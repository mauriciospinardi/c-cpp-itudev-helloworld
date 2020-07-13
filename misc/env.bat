@ECHO OFF

REM 
REM @file env.bat
REM @author Maurício Spinardi (mauricio.spinardi@setis.com.br)
REM @platform Verifone Engage V-OS2
REM @brief Verifone Development Environment
REM @date 2020-07-13
REM 
REM 

:ENVIRONMENT

SET ROOT_DIR=^
C:\cygwin64

SET PATH=^
%ROOT_DIR%\bin;^
%ROOT_DIR%\usr\x86_64-w64-mingw32\sys-root\mingw\bin;^
C:\Program Files\Git\bin;

EXIT /B 0
