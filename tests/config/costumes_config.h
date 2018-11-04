/*
 * BitLoom Costumes - A simple mocking framework for Bitloom projects
 *
 * Copyright (c) 2018 BlueZephyr
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef BL_COSTUMES_CONFIG_H
#define BL_COSTUMES_CONFIG_H

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


#endif // BL_COSTUMES_CONFIG_H
