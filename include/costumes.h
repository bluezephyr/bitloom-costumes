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

/*
 * Add an expected action of the specified type.  The type_name parameter is a string (name
 * of the type) that is used for debug purposes.  The max_usage parameter specifies the maximum
 * number of times the action may be used.   0 to specify no limit.  The parameter pointer is
 * used to hold expected parameters and the retval pointer is used in simlar way to hold the
 * return value that the mock will return to the module under test.  It is the responisbility
 * of the application to manage the memory for the parameter and the retval pointers.
 */
void costumes_add_expected_action_and_return(costumes_action_type_t type, const char* type_name,
                                             unsigned int max_usage, void *parameters, void* retval);

/*
 * Search the list of stored expected actions and find the first, not exhausted, action that matches.
 * The type must be correct and, if a pointer to a compare_t function is provided, the parameters in
 * the stored action will be compared with the provided (actual) parameters using the compare function.
 * If no matching action is found, true is returned and the retval pointer is set to the value
 * provided when the add_expect function was called.  If no matching action was found, false is
 * returned.
 */
bool costumes_is_action_expected(costumes_action_type_t type, compare_func_t *compare, void *actual, void **retval);

#endif // BL_COSTUMES_H
