#ifndef EMPLOYEE_H
#define EMPLOYEE_H

typedef struct employee {
  char first_name[32];
  char last_name[32];
  struct employee *boss;
} Employee;

int relation(Employee *employee1, Employee *employee2);
#endif
