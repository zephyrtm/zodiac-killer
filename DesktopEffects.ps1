Add-Type -AssemblyName System.Windows.Forms
Set-ExecutionPolicy Bypass -Scope Process
$shell = New-Object -ComObject Shell.Application
$desktop = $shell.Namespace(0)
$view = $desktop.Self.GetFolder().GetFolderView()
$screen = [System.Windows.Forms.Screen]::PrimaryScreen.Bounds
function Toggle-DesktopIcons {
    Add-Type @"
using System;
using System.Runtime.InteropServices;
public class Win32 {
    [DllImport("user32.dll")]
    public static extern IntPtr FindWindow(string lpClassName, string lpWindowName);
    [DllImport("user32.dll")]
    public static extern IntPtr SendMessage(IntPtr hWnd, uint Msg, IntPtr wParam, IntPtr lParam);
}
"@

    $WM_COMMAND = 0x111
    $TOGGLE_DESKTOP = 0x7402

    $desktop = [Win32]::FindWindow("Progman", $null)
    [Win32]::SendMessage($desktop, $WM_COMMAND, [IntPtr]$TOGGLE_DESKTOP, [IntPtr]0)
}
while ($true) {
    foreach ($item in $desktop.Items()) {
        Toggle-DesktopIcons
        $view.AutoArrange = $false
        $x = Get-Random -Minimum 0 -Maximum ($screen.Width - 100)
        $y = Get-Random -Minimum 0 -Maximum ($screen.Height - 100)
        $view.SelectItem($item, 0)
        $view.SetItemPosition($item, $x, $y)
    }
    Start-Sleep -Milliseconds 30
}

