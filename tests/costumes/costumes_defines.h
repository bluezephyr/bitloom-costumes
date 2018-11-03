/*
 * BitLoom Costumes - A simple mocking framework for Bitloom projects
 *
 * Copyright (c) 2018 BlueZephyr
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef BL_COSTUMES_DEFINES_TEST_H
#define BL_COSTUMES_DEFINES_TEST_H

#include <stdbool.h>

#define MAX_NO_OF_EXPECTED_ACTIONS 100

typedef enum
{
    no_param_action_one,
    no_param_action_two,
    int_parameter_action
} costumes_action_type_t;

typedef struct
{
    int value;
} int_action_parameter_type_t;


/********************************************************************
 * Core definitions
 ********************************************************************/
/*
 * This function declaration is used to determine if two stored
 * actions are identical.  The user must implement such function and
 * provide a pointer to it if parameters are used.
 */
typedef bool compare_parameters_func_t(void* expected, void* actual);

typedef struct
{
    costumes_action_type_t type;
    unsigned int max_usage;
    unsigned int used_times;
    bool exhausted;
    void* parameters;
} costumes_action_t;


#endif // BL_COSTUMES_DEFINES_TEST_H
