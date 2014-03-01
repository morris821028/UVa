@echo off
rem
rem pc2reset.bat - Completely reset and erase contest data
rem USE WITH EXTREME CAUTION 
rem 
rem $HeadURL: http://pc2.ecs.csus.edu/repos/pc2v9/branches/PC2_RELEASE_9_1_x/bin/pc2reset.bat $
rem

rem Windows 2000 and beyond syntax
set PC2BIN=%~dp0
if exist %PC2BIN%\pc2env.bat goto :continue

rem fallback to path (or current directory)
set PC2BIN=%0\..
if exist %PC2BIN%\pc2env.bat goto :continue

rem else rely on PC2INSTALL variable
set PC2BIN=%PC2INSTALL%\bin
if exist %PC2BIN%\pc2env.bat goto :continue

echo.
echo ERROR: Could not locate scripts.
echo.
echo Please set the variable PC2INSTALL to the location of
echo   the VERSION file (ex: c:\pc2-9.0.0)
echo.
pause
goto :end

:continue
call %PC2BIN%\pc2env.bat

set RMCMD=rmdir /s /q
if %OS%. == . set RMCMD=deltree /y

if not exist logs goto wrongdir
if not exist packets goto wrongdir

echo Backing up settings to archive 
call %PC2BIN%\pc2zip.bat

%RMCMD% logs
%RMCMD% packets
%RMCMD% reports
%RMCMD% db
%RMCMD% db.1
%RMCMD% db.2
%RMCMD% db.3

rem TODO execute*

goto end
:wrongdir

echo.
echo Not in directory to reset, should be run from dir with logs and packets
echo.


:end

rem eof pc2reset.bat $Id: pc2reset.bat 1761 2009-02-14 21:02:24Z boudreat $
