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


/*
 * List of all action types (costumes_action_type_t)
 */
#define no_param_action_one    (unsigned int)0
#define no_param_action_two    (unsigned int)1
#define int_parameter_action   (unsigned int)2

typedef struct
{
    int value;
} int_action_parameter_type_t;


#endif // BL_COSTUMES_CONFIG_H
