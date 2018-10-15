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

void costumes_init(void);
void costumes_add_expected_action(costumes_action_t action);

costumes_action_t * costumes_find_action(costumes_action_type_t type, void *parameters);

#endif // BL_COSTUMES_H
