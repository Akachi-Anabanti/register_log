cmake_minimum_required(VERSION 3.10)
project (RegisterLog C)

set (CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FPRINT REQUIRED libfprint-2)
pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(include ${FPRINT_INCLUDE_DIRS} ${GTK4_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(register_log ${SOURCE})

target_link_libraries(register_log
	${FPRINT_LIBRARIES}
	${GTK4_LIBRARIES}
	sqlite3
	)
