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
IF "%1" == "NEW" (
  
  echo generating documentation:
  make doc
  
) ELSE IF "%1" == "CLEAN" (
  
  echo removing documentation files
  rm -rf ../code/doc/html
  rm -f ../code/doc/log
  rm -f ../code/doc/log.txt
  
) ELSE (
  
  echo removing documentation files
  rm -rf ../code/doc/html
  rm -f ../code/doc/log
  rm -f ../code/doc/log.txt
  
  echo generating documentation:
  make doc
  
)