/*
 * BitLoom Costumes - A simple mocking framework for Bitloom projects
 *
 * Copyright (c) 2018 BlueZephyr
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef BL_COSTUMES_DEFINES_H
#define BL_COSTUMES_DEFINES_H

#include <stdbool.h>

/********************************************************************
 * Core definitions
 ********************************************************************/
#define MAX_NO_OF_EXPECTED_ACTIONS 100

/*
 * This function declaration is used to determine if two stored
 * actions are identical.  The user must implement such function and
 * provide a pointer to it if parameters are used.
 */
typedef bool compare_func_t(void* expected, void* actual);

/*
 * All actions must be defined by the application using costumes.
 */
typedef unsigned int costumes_action_type_t;

/*
 * Struct to hold one expected action.
 */
typedef struct
{
    costumes_action_type_t type;
    unsigned int max_usage;
    unsigned int used_times;
    bool exhausted;
    void* parameters;
    void *retval;
    const char *type_name;
} costumes_action_t;


#endif // BL_COSTUMES_DEFINES_H
