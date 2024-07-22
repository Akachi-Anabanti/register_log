#ifndef DATABASE_H
#define DATABASE_H

#include <time.h>


int initialize_database();
int update_staff_check_in_db(int staff_id, time_t check_in_time);
int update_staff_check_out_db(int staff_id, time_t check_out_time);
int add_visitor_log(const char *name, time_t check_in_time);
void close_database();

#endif // DATABASE_H
