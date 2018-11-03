/*
 * BitLoom Costumes - A simple mocking framework for Bitloom projects
 *
 * Copyright (c) 2018 BlueZephyr
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef BL_COSTUMES_H
#define BL_COSTUMES_H

#include "costumes_defines.h"

void costumes_create(void);
void costumes_destroy(void);
void costumes_add_expected_action(costumes_action_type_t type, unsigned int max_usage, void *parameters);

/*
 * Search the list of stored expected actions and find the first, not exhausted, action that matches.
 * The type must be correct and, if a pointer to a compare_parameters_t function is provided, the
 * parameters in the stored action will be compared with the provided parameters.  If no matching
 * action is found, NULL is returned.
 */
costumes_action_t* costumes_find_action(costumes_action_type_t type, compare_parameters_func_t *compare_parameters,
                                        void *parameters);

#endif // BL_COSTUMES_H
