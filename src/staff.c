#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/staff.h"
#include "../include/database.h"
#include "../include/fingerprint.h"

#define MAX_NAME_LENGTH 100

struct Staff {
	int id;
	char name[MAX_NAME_LENGTH];
	time_t last_check_in;
	time_t last_check_out;
};

Staff* create_staff(int id, const char *name)
{
	Staff *staff = (Staff*)malloc(sizeof(Staff));
	if (staff == NULL)
	{
		return NULL;
	}

	staff->id = id;
	strncpy(staff->name, name, MAX_NAME_LENGTH - 1);
	staff->name[MAX_NAME_LENGTH - 1] = '\0';
	staff->last_check_in = 0;
	staff_last_check_out = 0;

	return staff;
}

int staff_check _in(Staff* staff)
{
	if (staff == NULL) return 0;
	if (!verify_fingerprint())
	{
		printf("Fingerprint verification failed.\n");
		return 0;
	}

	time_t now = time(NULL);
	staff->last_check_in = now;

	if (!update_staff_check_in_db(staff->id, now))
	{
		printf("Failed to update database.\n");
	}

	printf("%s checked in at %s", staff->name, ctime(&now));
	return 1;
}


int staff_check_out(Staff *staff)
{
	if (staff == NULL) return 0;
	if (!verify_fingerprint())
	{
		printf("Fingerprint verification failed .\n");
		return 0;
	}

	time_t now = time(NULL);
	staff->last_check_out = now;

	if (!update_staff_check_out_db(staff->id, now))
	{
		printf("Failed to update database. \n");

		return 0;

	}

	printf("%s checked out at %s", staff->name, ctime(&now));
	return 1
}

void free_staff(Staff *staff)
{
	free(staff);
}
