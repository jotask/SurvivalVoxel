@echo off
call premake5.exe vs2017
IF %ERRORLEVEL% NEQ 0 (
  PAUSE
)