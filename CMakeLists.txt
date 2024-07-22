cmake_minimum_required(VERSION 3.10)
project (RegisterLog C)

set (CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FPRINT REQUIRED Libfprint-2)


include_directories(include ${FPRINT_INCLUDE_DIRS})

add_executable(register_log
	src/main.c
	src/staff.c
	src/visitor.c
	src/database.c
	)

target_link_libraries(register_log ${FPRINT_LIBRARIES} sqlite3)
