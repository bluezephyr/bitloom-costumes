/*
 * Unit tests for the Bitloom costumes module.
 *
 * Copyright (c) 2018. BlueZephyr
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include <unity_fixture.h>
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
    RUN_TEST_CASE(costumes, add_expected_action_no_parameters_use_once_ok);
    RUN_TEST_CASE(costumes, add_expected_action_no_parameters_use_twice_ok);
    RUN_TEST_CASE(costumes, add_expected_action_no_parameters_use_too_many_times);
    RUN_TEST_CASE(costumes, add_several_expected_actions_find_one);
    RUN_TEST_CASE(costumes, actions_with_parameters_find_correct_action);
    RUN_TEST_CASE(costumes, actions_with_parameters_action_not_found);
    RUN_TEST_CASE(costumes, actions_with_parameters_find_exhaust_all_previous_actions_of_same_type);
}

TEST_SETUP(costumes)
{
    costumes_create();
}

TEST_TEAR_DOWN(costumes)
{
    costumes_destroy();
}

/********************************************************************
 * Local function prototypes
 ********************************************************************/
static void* create_int_parameters(int value);
static void check_no_param_action(const costumes_action_type_t expected_action_type,
                                  const costumes_action_t* fetched_action);
static void test_find_action_number_of_times(int no_of_times);

/* Function to compare parameters of int_action_parameter_type_t */
static bool int_parameter_comparator (void* expected, void* actual);

/********************************************************************
 * TEST CASES
********************************************************************/
TEST(costumes, add_expected_action_no_parameters)
{
    costumes_action_t* fetched_action;

    costumes_add_expected_action(no_param_action_one, 0, NULL);
    fetched_action = costumes_find_action(no_param_action_one, NULL, NULL);
    check_no_param_action(no_param_action_one, fetched_action);
}

TEST(costumes, add_expected_action_no_parameters_use_once_ok)
{
    test_find_action_number_of_times(1);
}

TEST(costumes, add_expected_action_no_parameters_use_twice_ok)
{
    test_find_action_number_of_times(2);
}

static void test_find_action_number_of_times(int no_of_times)
{
    int i;
    costumes_action_t* fetched_action;

    costumes_add_expected_action(no_param_action_one, no_of_times, NULL);
    for (i=0; i < no_of_times - 1; i++)
    {
        (void*) costumes_find_action(no_param_action_one, NULL, NULL);
    }
    fetched_action = costumes_find_action(no_param_action_one, NULL, NULL);
    check_no_param_action(no_param_action_one, fetched_action);
}

TEST(costumes, add_expected_action_no_parameters_use_too_many_times)
{
    costumes_action_t *fetched_action;

    costumes_add_expected_action(no_param_action_one, 1, NULL);
    (void*) costumes_find_action(no_param_action_one, NULL, NULL);
    fetched_action = costumes_find_action(no_param_action_one, NULL, NULL);

    TEST_ASSERT_NULL(fetched_action);
}

TEST(costumes, add_several_expected_actions_find_one)
{
    costumes_action_t* fetched_action;

    costumes_add_expected_action(no_param_action_one, 0, NULL);
    costumes_add_expected_action(no_param_action_two, 0, NULL);

    fetched_action = costumes_find_action(no_param_action_one, NULL, NULL);
    check_no_param_action(no_param_action_one, fetched_action);
}

TEST(costumes, actions_with_parameters_find_correct_action)
{
    costumes_action_t* fetched_action;
    int_action_parameter_type_t expected_parameters;

    costumes_add_expected_action(int_parameter_action, 0, create_int_parameters(1));
    costumes_add_expected_action(int_parameter_action, 0, create_int_parameters(2));
    expected_parameters.value = 2;

    fetched_action = costumes_find_action(int_parameter_action, int_parameter_comparator, &expected_parameters);
    TEST_ASSERT_EQUAL_INT(2, ((int_action_parameter_type_t*)fetched_action->parameters)->value);
    TEST_ASSERT_EQUAL_INT(1, fetched_action->used_times);
}

TEST(costumes, actions_with_parameters_action_not_found)
{
    int_action_parameter_type_t expected_parameters;

    costumes_add_expected_action(int_parameter_action, 0, create_int_parameters(1));
    expected_parameters.value = 3;

    TEST_ASSERT_NULL(costumes_find_action(int_parameter_action, int_parameter_comparator, &expected_parameters));
}

TEST(costumes, actions_with_parameters_find_exhaust_all_previous_actions_of_same_type)
{
    costumes_action_t* fetched_action;
    int_action_parameter_type_t expected_parameters;

    costumes_add_expected_action(int_parameter_action, 0, create_int_parameters(1));
    costumes_add_expected_action(int_parameter_action, 0, create_int_parameters(2));

    expected_parameters.value = 2;
    (void*)costumes_find_action(int_parameter_action, int_parameter_comparator, &expected_parameters);
    expected_parameters.value = 1;

    // The find off the second action exhausts the first action of the same type
    TEST_ASSERT_NULL(costumes_find_action(int_parameter_action, int_parameter_comparator, &expected_parameters));
}


/********************************************************************
 * Local function implementations
 ********************************************************************/
static void* create_int_parameters(int value)
{
    int_action_parameter_type_t* parameters;

    parameters = malloc(sizeof(int_action_parameter_type_t));
    parameters->value = value;
    return parameters;
}

static void check_no_param_action(const costumes_action_type_t expected_action_type,
                                  const costumes_action_t* fetched_action)
{
    TEST_ASSERT_NOT_NULL(fetched_action);
    TEST_ASSERT_EQUAL_INT(expected_action_type, fetched_action->type);
    TEST_ASSERT_EQUAL_PTR(NULL, fetched_action->parameters);
}

static bool int_parameter_comparator(void *expected, void *actual)
{
    if ((expected != NULL) && (actual != NULL))
    {
        if (((int_action_parameter_type_t*)expected)->value ==
                ((int_action_parameter_type_t*)actual)->value)
        {
            return true;
        }
    }
    return false;
}
