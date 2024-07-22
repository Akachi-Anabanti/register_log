#ifndef STAFF_H
#define STAFF_H

typedef struct Staff Staff;

Staff *create_staff(int id, const char *name);
int staff_check_in(Staff *staff);
int staff_check_out(Staff *staff);
void free_staff(Staff *staff);

#endif //STAFF_H
