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
C:\Program Files\Git\bin;

EXIT /B 0
