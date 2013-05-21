REM @echo off

REM Ordner wechseln
IF %2!==! ( 
  REM nichts machen
) ELSE (
  cd %2\..\scripts
)

REM PORT ermitteln
IF %3!==! (
  set gdbport=1234
) ELSE (
  set gdbport=%3
)

@call console.bat

REM und ausfuehren
IF "%1" == "DEBUG" ( 
  echo start QEMU, waiting for GDB
  start /B qemu.exe -S -gdb tcp::1234,nowait,nodelay,server,ipv4 -kernel ..\code\bin\oostubs
  
  %SystemRoot%\system32\ping -n 3 localhost> nul
  
  echo start GDB
  start cmd /C gdb -x ..\code\misc\gdb.script ..\code\bin\oostubs
  
) ELSE (
  
  echo start QEMU
  start /B qemu.exe -gdb tcp::1234,nowait,nodelay,server,ipv4 -kernel ..\code\bin\oostubs
  
)

