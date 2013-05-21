@echo off

SET LANG=C

REM Ordner wechseln
IF %2!==! ( 
  REM nichts machen
) ELSE (
  cd %2\..\scripts
)

call console.bat
cd ..\code

REM je nach dem, was gemacht werden soll, machen
IF "%1" == "BUILD" (
  
  make
  
) ELSE IF "%1" == "CLEAN" (
  
  make clean
  
) ELSE (
  
  make clean
  make
  
)