@echo off

SET LANG=C

REM Ordner wechseln
IF %1!==! ( 
  REM nichts machen
) ELSE (
  cd %1\..\scripts
)

call console.bat
cd ..\code

echo open documentation index file
.\doc\html\index.html