*
* vi:ts=6:sw=6:ai:ic
*
* File: sum.f
* Purpose: to sum the numbers from num.dat
* Source: Fortran 77 (compiled under Linux/fort77)
* Author: pc2@ecs.csus.edu (laned)
* Source: FORTRAN 77
* OS: Tested under Linux  
* $Id: sumit.f 326 2006-10-25 02:53:57Z laned $
*
*23456789 
* On Open the STATUS can be:
*
* 'OLD' - file exists 
* 'NEW" - create the file
* 'SCRATCH' - this file is only used as long as the program runs
* 'UNKNOWN' - none of the above, depends on OS
*
* IOSTAT returns an INTEGER 
* .eq. 0  - OK
* .lt. 0 - error during I/O
* .gt. 0 - EOF
*

*23456789 

	INTEGER IOS
	INTEGER IVALUE
	INTEGER THESUM
	CHARACTER INFILE * 20

	INFILE = 'sumit.dat'

	THESUM = 0

      OPEN (UNIT = 5, FILE=INFILE, STATUS='OLD', IOSTAT=IOS)

	IF (IOS .NE. 0) GOTO 200 

 100  CONTINUE

 	READ (5, 500, IOSTAT = IOS) IVALUE
* 	READ (5, '(I)', IOSTAT = IOS) IVALUE

	IF (IVALUE .GT. 0) THEN
 		THESUM = THESUM + IVALUE
 	END IF

	IF (IOS .NE. 0) GOTO 200 
	IF (IVALUE .EQ. 0) GOTO 200

	GOTO 100

 200  CONTINUE 

 	IF (IOS .EQ. 2) THEN
	  PRINT *, 'FILE NOT FOUND ',INFILE
	  STOP
 	ELSE IF (IOS .GT. 0) THEN
	  PRINT *, 'ERROR NUMBER', IOS, ' ON FILE ',INFILE
	  STOP
	END IF

	PRINT *, 'The sum of the integers is ',THESUM

      CLOSE (UNIT = 5)

 500  FORMAT (I12)

*23456789 
      END
