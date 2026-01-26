Add-Type -AssemblyName System.Windows.Forms
Set-ExecutionPolicy Bypass -Scope Process
$shell = New-Object -ComObject Shell.Application
$desktop = $shell.Namespace(0)
$view = $desktop.Self.GetFolder().GetFolderView()
$view.AutoArrange = $false
$screen = [System.Windows.Forms.Screen]::PrimaryScreen.Bounds
while ($true) {
    foreach ($item in $desktop.Items()) {
        $x = Get-Random -Minimum 0 -Maximum ($screen.Width - 100)
        $y = Get-Random -Minimum 0 -Maximum ($screen.Height - 100)
        $view.SelectItem($item, 0)
        $view.SetItemPosition($item, $x, $y)
    }
    Start-Sleep -Milliseconds 30
}
