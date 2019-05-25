#include "timeit.h"

#include <assert.h>
#include <stdlib.h>  // for random(), srandom()
#include <stdbool.h> // for bool
#include <stdint.h>
#include <time.h>    // for time()


struct Employee_With_Bool_Flag {
    char name[24];
    char address[32];
    bool from_army;  // if employee ever serviced in army
    double salary;
    
};

struct Employee_Without_Bool_Flag {
    char name[24];
    char address[32];
    double salary;
};

typedef struct Employee_With_Bool_Flag EmployeeF;
typedef struct Employee_Without_Bool_Flag EmployeeNF; //NF: no flag


int rand_int(int a, int b)
{
    assert(a < b);
    return (random() % (b-a)) + a;
}


void init_employeef(EmployeeF* e)
{
    static uint64_t id = 0;
    e->salary = (double)rand_int(1000, 20000);
    e->from_army = (id++ % 1000 == 0);
}


void init_employeefs(EmployeeF* e, int num)
{
    srandom(time(NULL));
    for (int i = 0; i < num; i++) {
        init_employeef(e+i);
    }
}


/* Increase salary by 500 if employee ever serviced in army. */
void increase_salary_with_flag(EmployeeF *e, int num)
{
    for (int i = 0; i < num; i++) {
        if (e[i].from_army) {
            e[i].salary += 500;
        }
    }
}

void init_employeenf(EmployeeNF* e, bool *from_army_flag)
{
    static uint64_t id = 0;
    e->salary = (double)rand_int(1000, 20000);
    *from_army_flag = (rand_int(0, 10) % 1000 == 0);
}


void init_employeenfs(EmployeeNF* e, bool *from_army_flags, int num)
{
    srandom(time(NULL));
    for (int i = 0; i < num; i++) {
        init_employeenf(e+i, from_army_flags+i);
    }
}


/* Increase salary by 500 if employee ever serviced in army. */
void increase_salary_with_separate_flag(EmployeeNF *e, bool *from_army_flags, int num)
{
    for (int i = 0; i < num; i++) {
        if (from_army_flags[i]) {
            e[i].salary += 500;
        }
    }
}


int main(int argc, char **argv)
{
    
    EmployeeF* employees1;
    EmployeeNF* employees2;
    bool *from_army_flags;

    if (argc != 3) { 
        printf("Usage: ./test_flag_storing ${employee_num} ${mode}\n");
        exit(-1);
    }


    int num = atoi(argv[1]);
    int mode = atoi(argv[2]);

    if (mode == 0) {
        employees1 = (EmployeeF*) malloc(num * sizeof(EmployeeF));
        init_employeefs(employees1, num);
        printf("increase_salary_with_flag(EmployeeF*, %d):\n", num);
        timeit(1, increase_salary_with_flag, employees1, num);
        free(employees1);
    } else {
        employees2 = (EmployeeNF*) malloc(num * sizeof(EmployeeNF));
        from_army_flags = (bool *) malloc(num * sizeof(bool));
        init_employeenfs(employees2, from_army_flags, num);

        printf("increase_salary_with_separate_flag(EmployeeNF*, %d):\n", num);
        timeit(1, increase_salary_with_separate_flag, employees2, from_army_flags, num);

        free(employees2);
        free(from_army_flags);
    }
    printf("\n");
}
