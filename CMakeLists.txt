cmake_minimum_required(VERSION 3.16)
project(wServer C)

set(CMAKE_C_STANDARD 11)

macro (FindSQLite3)
    # Look for the library.
    # find_path(SQLITE3_INCLUDE_DIR NAMES libsqlite3)

    find_path(SQLITE3_INCLUDE_DIR NAMES sqlite3.h)

    find_library(SQLITE3_LIBRARY NAMES libsqlite3)

    # Handle the QUIETLY and REQUIRED arguments and set SQLITE3_FOUND to TRUE if all listed variables are TRUE.
    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(SQLITE3 DEFAULT_MSG SQLITE3_LIBRARY SQLITE3_INCLUDE_DIR)

    # Copy the results to the output variables.
    if (SQLITE3_FOUND)
        set (SQLITE3_LIBRARIES ${SQLITE3_LIBRARY})
        set (SQLITE3_INCLUDE_DIRS ${SQLITE3_INCLUDE_DIR})
        message(SQLite3 Found ${SQLITE3_INCLUDE_DIRS} ${SQLITE3_LIBRARY})
    else (SQLITE3_FOUND)
        set (SQLITE3_LIBRARIES)
        set (SQLITE3_INCLUDE_DIRS)
        message(SQLite3 not Found)
    endif (SQLITE3_FOUND)

    mark_as_advanced (SQLITE3_INCLUDE_DIRS SQLITE3_LIBRARIES)
endmacro()

include_directories(.)
include_directories(inc)
include_directories(libmx)
include_directories(libmx/inc)
include_directories(libmx/src)
include_directories(src)

add_executable(wServer
        inc/uchat.h
        libmx/inc/libmx.h
        libmx/src/mx_atoi.c
        libmx/src/mx_binary_search.c
        libmx/src/mx_bubble_sort.c
        libmx/src/mx_count_substr.c
        libmx/src/mx_count_words.c
        libmx/src/mx_create_node.c
        libmx/src/mx_del_extra_spaces.c
        libmx/src/mx_del_strarr.c
        libmx/src/mx_delete_list.c
        libmx/src/mx_file_to_str.c
        libmx/src/mx_foreach.c
        libmx/src/mx_get_char_index.c
        libmx/src/mx_get_substr_index.c
        libmx/src/mx_hex_to_nbr.c
        libmx/src/mx_isalpha.c
        libmx/src/mx_isdigit.c
        libmx/src/mx_isspace.c
        libmx/src/mx_itoa.c
        libmx/src/mx_list_size.c
        libmx/src/mx_memccpy.c
        libmx/src/mx_memchr.c
        libmx/src/mx_memcmp.c
        libmx/src/mx_memcpy.c
        libmx/src/mx_memmem.c
        libmx/src/mx_memmove.c
        libmx/src/mx_memrchr.c
        libmx/src/mx_memset.c
        libmx/src/mx_nbr_to_hex.c
        libmx/src/mx_pop_back.c
        libmx/src/mx_pop_front.c
        libmx/src/mx_pow.c
        libmx/src/mx_print_strarr.c
        libmx/src/mx_print_unicode.c
        libmx/src/mx_printchar.c
        libmx/src/mx_printerr.c
        libmx/src/mx_printint.c
        libmx/src/mx_printstr.c
        libmx/src/mx_push_back.c
        libmx/src/mx_push_front.c
        libmx/src/mx_quicksort.c
        libmx/src/mx_read_line.c
        libmx/src/mx_realloc.c
        libmx/src/mx_replace_substr.c
        libmx/src/mx_sort_list.c
        libmx/src/mx_sqrt.c
        libmx/src/mx_str_reverse.c
        libmx/src/mx_strcat.c
        libmx/src/mx_strcmp.c
        libmx/src/mx_strcpy.c
        libmx/src/mx_strdel.c
        libmx/src/mx_strdup.c
        libmx/src/mx_strjoin.c
        libmx/src/mx_strlen.c
        libmx/src/mx_strncat.c
        libmx/src/mx_strncmp.c
        libmx/src/mx_strncpy.c
        libmx/src/mx_strndup.c
        libmx/src/mx_strnew.c
        libmx/src/mx_strsplit.c
        libmx/src/mx_strstr.c
        libmx/src/mx_strtrim.c
        libmx/src/mx_swap_char.c
        src/libs/base64.c
        src/libs/handshake.c
        src/libs/sha1.c
        src/sqlite3/sqlite3.c
        src/uchat_server.c)
