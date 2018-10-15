/*
 * Unit tests for the Bitloom costumes module.
 *
 * Copyright (c) 2018. BlueZephyr
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "unity_fixture.h"
#include "costumes.h"
#include "costumes_defines.h"

/*
 * Tests to be written:
 * - TBD
 */

TEST_GROUP(costumes);
TEST_GROUP_RUNNER(costumes)
{
    RUN_TEST_CASE(costumes, add_expected_action_no_parameters);
    RUN_TEST_CASE(costumes, add_several_expected_actions_find_one);
}

TEST_SETUP(costumes)
{
    costumes_init();
}

TEST_TEAR_DOWN(costumes)
{
}

/********************************************************************
 * Local function prototypes
 ********************************************************************/
static costumes_action_t create_no_parameter_action(costumes_action_type_t action);
static void check_no_param_action(const costumes_action_t* expected_action,
                                  const costumes_action_t* fetched_action);


/********************************************************************
 * TEST CASES
********************************************************************/
TEST(costumes, add_expected_action_no_parameters)
{
    costumes_action_t stored_action = create_no_parameter_action(no_param_action_one);
    costumes_action_t* fetched_action;

    costumes_add_expected_action(stored_action);
    fetched_action = costumes_find_action(no_param_action_one, NULL);

    check_no_param_action(&stored_action, fetched_action);
}

TEST(costumes, add_several_expected_actions_find_one)
{
    costumes_action_t* fetched_action;
    costumes_action_t stored_one = create_no_parameter_action(no_param_action_one);
    costumes_action_t stored_two = create_no_parameter_action(no_param_action_two);

    costumes_add_expected_action(stored_one);
    costumes_add_expected_action(stored_two);

    fetched_action = costumes_find_action(no_param_action_one, NULL);
    check_no_param_action(&stored_one, fetched_action);
}

/********************************************************************
 * Local function implementations
 ********************************************************************/
static void check_no_param_action(const costumes_action_t* expected_action,
                                  const costumes_action_t* fetched_action)
{
    TEST_ASSERT_NOT_NULL(fetched_action);
    TEST_ASSERT_EQUAL_INT(expected_action->type, fetched_action->type);
    TEST_ASSERT_EQUAL_PTR(NULL, fetched_action->parameters);
}

static costumes_action_t create_no_parameter_action(costumes_action_type_t type)
{
    costumes_action_t action;
    action.parameters = NULL;
    action.type = type;
    return action;
}

