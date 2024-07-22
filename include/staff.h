#ifndef STAFF_H
#define STAFF_H

#define MAX_NAME_LENGTH 100

struct Staff {
	int id;
	char name[MAX_NAME_LENGTH];
	time_t last_check_in;
	time_t last_check_out;
};

typedef struct Staff Staff;

Staff *create_staff(int id, const char *name);
int enroll_new_staff(const char *name);
int staff_check_in(Staff *staff);
int staff_check_out(Staff *staff);
void free_staff(Staff *staff);

#endif //STAFF_H
