#ifndef _EMPLOYEE_H
#define _EMPLOYEE_H
 
struct employee{
    int id;
    char first_name[32];
    char last_name[32];
    int boss_id;
};
typedef struct employee Employee;
 
void init_storage(Employee **storage, int n);
void free_storage(Employee **storage);
Employee* find_employee_by_id( Employee *set, int n, int id );
Employee* find_employee_by_name( Employee *set, int n, const char *first_name, const char *last_name );
Employee* find_root_boss( Employee *set, int n, Employee *employee );
int check_relationship(Employee *set, int n, Employee *A, Employee *B);
 
#endif
