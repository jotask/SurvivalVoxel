@echo off

IF EXIST "build" (
    rmdir "build" /s /q
)

IF EXIST ".vs" (
    rmdir ".vs" /s /q
)