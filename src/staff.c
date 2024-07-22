#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/staff.h"
#include "../include/database.h"
#include "../include/fingerprint.h"


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
	staff->last_check_out = 0;

	return staff;
}

int enroll_new_staff(const char *name)
{
	int new_id = get_next_staff_id();
	if (new_id -1)
	{
		printf("Failed to get new staff ID.\n");
		return 0;
	}

	Staff *new_staff = create_staff(new_id, name);
	if (new_staff == NULL)
	{
		printf("Failed to create new staff.\n");
		return 0;
	}

	if (!add_staff_to_db(new_staff))
	{
		printf("Failed to add staff to database.\n");
		free_staff(new_staff);
		return 0;
	}

	printf("Enrolling fingerprint for %s (ID %d) \n", name, new_id);
	if (!enroll_fingerprint(new_id)){
		printf("Failed to enroll fingerprint .\n");
		free_staff(new_staff);
		return 0;
	}

	printf("Staff member %s (ID: %d) successfully enrolled .\n", name, new_id);
	free_staff(new_staff);
	return 1;
}

int staff_check_in(Staff* staff)
{
	if (staff == NULL) return 0;
	if (!verify_fingerprint(staff->id))
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
	if (!verify_fingerprint(staff->id))
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
	return 1;
}

void free_staff(Staff *staff)
{
	free(staff);
}
