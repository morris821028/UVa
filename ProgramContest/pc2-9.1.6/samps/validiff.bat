@echo off
rem 
rem  File:    validdiff
rem  Purpose: to show gvim diff and also execute internal PC^2 Validator
rem 
rem  $HeadURL: http://pc2.ecs.csus.edu/repos/pc2v9/branches/PC2_RELEASE_9_1_x/samps/validiff.bat $
rem  $Id: validiff.bat 1052 2007-11-10 22:59:34Z laned $
rem 
rem  Directions
rem  Add/Edit Problem | Validator Tab 
rem  Select Use External Validator
rem  Validator Command Line must be: {:infile} {:outfile} {:ansfile} {:resfile} 
rem  

java -cp /usr/pc2v9/lib/pc2.jar edu.csus.ecs.pc2.validator.Validator $* -pc2 1 true

gvim -d $2 $3 > NUL

rem  eof validiff
