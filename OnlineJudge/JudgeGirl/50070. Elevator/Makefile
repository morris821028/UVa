all: ta_main stu_main

ta_main: ta_main.c elevator.c
	gcc -std=c99 -O2 ta_main.c elevator.c -o ta_main

stu_main: main.c ta_elevator.c
	gcc -std=c99 -O2 main.c ta_elevator.c -o stu_main
