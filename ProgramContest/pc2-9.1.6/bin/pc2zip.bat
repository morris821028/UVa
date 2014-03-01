@echo off

rem Purpose: print pc2 version number
rem Author : pc2@ecs.csus.edu
rem $HeadURL: http://pc2.ecs.csus.edu/repos/pc2v9/branches/PC2_RELEASE_9_1_x/bin/pc2zip.bat $

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
java -Xms64M -Xmx768M -cp %libdir%\pc2.jar edu.csus.ecs.pc2.core.archive.ZipPC2

:end
rem eof pc2ver.bat $Id: pc2zip.bat 1761 2009-02-14 21:02:24Z boudreat $
