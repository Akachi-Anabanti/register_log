#include <stdio.h>
#include <sqlite3.h>
#include <time.h>
#include "../include/database.h"
#include "../include/staff.h"

/**Database instance */
static sqlite3 *db;


/**Setup the database schema */
int initialize_database()
{
	int rc = sqlite3_open("register_log.db", &db);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 0;
	}

	const char *sql_create_staff_table = "CREATE TABLE IF NOT EXISTS staff ("
										 "id INTEGER PRIMARY KEY,"
										 "name TEXT NOT NULL,"
										 "last_check_in INTEGER,"
										 "last_check_out INTEGER);";
	const char *sql_create_visitor_table = "CREATE TABLE IF NOT EXISTS visitors ("
											"id INTEGER PRIMARY KEY AUTOINCREMENT,"
											"name TEXT NOT NULL,"
											"check_in_time INTEGER NOT NULL,"
											"check_out_time INTEGER);";
	rc = sqlite3_exec(db, sql_create_staff_table, 0, 0, 0);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
		return 0;
	}

	rc = sqlite3_exec(db, sql_create_visitor_table, 0, 0, 0);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
		return 0;
	}

	return 1;
}


/*CRUD OPERATIONS*/
int update_staff_check_in_db(int staff_id, time_t check_in_time)
{
	const char *sql = "UPDATE staff SET last_check_in = ? WHERE id = ?;";

	sqlite3_stmt *stmt;

	int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
	if (rc != SQLITE_OK){
		fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
		return 0;
	}

	sqlite3_bind_int64(stmt, 1, (sqlite3_int64)check_in_time);
	sqlite3_bind_int(stmt, 2, staff_id);

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE)
	{
		fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		return 0;
	}
	sqlite3_finalize(stmt);
	return 1;
}

int update_staff_check_out_db(int staff_id, time_t check_out_time)
{
	const char *sql = "UPDATE staff SET last_check_out = ? WHERE id = ?;";

	sqlite3_stmt *stmt;

	int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
	if (rc != SQLITE_OK){
		fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
		return 0;
	}

	sqlite3_bind_int64(stmt, 1, (sqlite3_int64)check_out_time);
	sqlite3_bind_int(stmt, 2, staff_id);

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE)
	{
		fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		return 0;
	}
	sqlite3_finalize(stmt);
	return 1;
}

int add_visitor_log(const char *name, time_t check_in_time)
{
	const char *sql = "INSERT INTO visitors (name, check_in_time) VALUES (?, ?);";
	sqlite3_stmt *stmt;
	
	int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
	if (rc != SQLITE_OK){
		fprintf(stderr, "Failed to prepare statements: %s\n", sqlite3_errmsg(db));
		return 0;
	}

	sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
	sqlite3_bind_int64(stmt, 2, (sqlite3_int64)check_in_time);


	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE){
		fprintf(stderr, "Execution fialed: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		return 0;
	}

	sqlite3_finalize(stmt);
	return 1;
}


int get_next_staff_id(){
	const char *sql = "SELECT MAX(id) FROM staff;";
	sqlite3_stmt *stmt;
	int max_id = 0;

	int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
	if (rc != SQLITE_OK){
		fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
		return -1;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW){
		max_id = sqlite3_column_int(stmt, 0);
	}

	sqlite3_finalize(stmt);
	return max_id + 1;
}

int add_staff_to_db(Staff *staff)
{
	const char *sql = "INSERT INTO staff (id, name) VALUES (?, ?);";
	sqlite3_stmt *stmt;

	int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
	if (rc != SQLITE_OK){
		fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
		return 0;
	}

	sqlite3_bind_int(stmt, 1, staff->id);
	sqlite3_bind_text(stmt, 2, staff->name, -1, SQLITE_STATIC);

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE)
	{
		fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		return 0;
	}

	sqlite3_finalize(stmt);
	return 1;

}

Staff *get_staff_by_id(int id){
	const char *sql = "SELECT name FROM staff WHERE id = ?;";
	sqlite3_stmt *stmt;
	Staff *staff = NULL;

	int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
	if (rc != SQLITE_OK){
		fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
		return NULL;
	}

	sqlite3_bind_int(stmt, 1, id);

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW){
		const char *name = (const char *)sqlite3_column_text(stmt, 0);
		staff = create_staff(id, name);
	}

	sqlite3_finalize(stmt);
	return staff;
}

/*Close the database after operations */
void close_database(){
	sqlite3_close(db);
}