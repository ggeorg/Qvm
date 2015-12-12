cmake_minimum_required (VERSION 2.6)
project (Qvm)

# The version number.
set (Qvm_VERSION_MAJOR 0)
set (Qvm_VERSION_MINOR 1)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
	"${PROJECT_SOURCE_DIR}/QvmConfig.h.in"
	"${PROJECT_BINARY_DIR}/QvmConfig.h"
)

# use PkgConfig
find_package(PkgConfig REQUIRED)

# bdw-gc
pkg_check_modules(GC REQUIRED bdw-gc)

# glib-2.0
pkg_check_modules(GLIB2 REQUIRED glib-2.0)
#set(GLIB2_LIBS glib2)

# gmodule-2.0
pkg_check_modules(GMODULE2 REQUIRED gmodule-2.0)

# libffi
pkg_check_modules(LIBFFI REQUIRED libffi)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories (
	"${PROJECT_BINARY_DIR}"
	${GC_INCLUDE_DIRS}
	${GLIB2_INCLUDE_DIRS}
	${GMODULE2_INCLUDE_DIRS}
	${LIBFFI_INCLUDE_DIRS}
)

link_directories (
	${GC_LIBRARY_DIRS}
	${GLIB2_LIBRARY_DIRS}
	${GMODULE2_LIBRARY_DIRS}
	${LIBFFI_LIBRARY_DIRS}
)

# sends the -std=c99 flag to the gcc compiler
add_definitions(-std=c99 ${GC_CFLAGS_OTHER})

# add the executable
add_executable (
	Qvm
	src/main.c
	src/Qvm.c 
	src/operations.c
	src/qvm-gc.c
	src/_types.c
	src/as/Qas.c
)

target_link_libraries (
	Qvm
	${GC_LIBRARIES} 
	${GLIB2_LIBRARIES} 
	${GMODULE2_LIBRARIES}
	${LIBFFI_LIBRARIES}
	${LIBPTHREAD_LIBRARIES}
	pthread
	m
)


