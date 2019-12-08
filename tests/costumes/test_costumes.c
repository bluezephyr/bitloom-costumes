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
#include "costumes_config.h"

/*
 * Tests to be written:
 * - TBD
 */

TEST_GROUP(costumes);
TEST_GROUP_RUNNER(costumes)
{
    RUN_TEST_CASE(costumes, add_expected_action_no_parameters_no_retval);
    RUN_TEST_CASE(costumes, add_expected_action_no_parameters_with_retval);
    RUN_TEST_CASE(costumes, add_expected_action_no_parameters_use_once_ok);
    RUN_TEST_CASE(costumes, add_expected_action_no_parameters_use_too_many_times);
    RUN_TEST_CASE(costumes, add_expected_action_no_parameters_use_twice_ok);
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
 * LOCAL FUNCTION PROTOTYPES
 ********************************************************************/
static void* create_int_parameters(int value);

/* Function to compare parameters of int_action_parameter_type_t */
static bool int_parameter_comparator (void* expected, void* actual);


/********************************************************************
 * DEFINES
********************************************************************/
#define EXPECTED_RETVAL 5


/********************************************************************
 * TEST CASES
********************************************************************/
TEST(costumes, add_expected_action_no_parameters_no_retval)
{
    void *retval;
    costumes_add_expected_action_and_return(no_param_action_one, NULL, 0, NULL, NULL);
    TEST_ASSERT_TRUE(costumes_is_action_expected(no_param_action_one, NULL, NULL, &retval));
}

TEST(costumes, add_expected_action_no_parameters_with_retval)
{
    int expected_retval = EXPECTED_RETVAL;
    void *retval_ptr;

    costumes_add_expected_action_and_return(no_param_action_one, NULL, 0, NULL, &expected_retval);
    TEST_ASSERT_TRUE(costumes_is_action_expected(no_param_action_one, NULL, NULL, &retval_ptr));
    TEST_ASSERT_EQUAL_INT(expected_retval, (*(int*)retval_ptr));
}

TEST(costumes, add_expected_action_no_parameters_use_once_ok)
{
    int expected_retval = EXPECTED_RETVAL;
    void *retval_ptr;

    costumes_add_expected_action_and_return(no_param_action_one, NULL, 1, NULL, &expected_retval);
    TEST_ASSERT_TRUE(costumes_is_action_expected(no_param_action_one, NULL, NULL, &retval_ptr));
    TEST_ASSERT_EQUAL_INT(expected_retval, (*(int*)retval_ptr));
}

TEST(costumes, add_expected_action_no_parameters_use_too_many_times)
{
    int expected_retval = EXPECTED_RETVAL;
    void *retval_ptr;

    costumes_add_expected_action_and_return(no_param_action_one, NULL, 1, NULL, &expected_retval);
    TEST_ASSERT_TRUE(costumes_is_action_expected(no_param_action_one, NULL, NULL, &retval_ptr));
    TEST_ASSERT_FALSE(costumes_is_action_expected(no_param_action_one, NULL, NULL, &retval_ptr));
}

TEST(costumes, add_expected_action_no_parameters_use_twice_ok)
{
    int expected_retval = EXPECTED_RETVAL;
    void *retval_ptr;

    costumes_add_expected_action_and_return(no_param_action_one, NULL, 2, NULL, &expected_retval);
    TEST_ASSERT_TRUE(costumes_is_action_expected(no_param_action_one, NULL, NULL, &retval_ptr));
    TEST_ASSERT_TRUE(costumes_is_action_expected(no_param_action_one, NULL, NULL, &retval_ptr));
    TEST_ASSERT_EQUAL_INT(expected_retval, (*(int*)retval_ptr));
}

TEST(costumes, add_several_expected_actions_find_one)
{
    void *retval_ptr;

    costumes_add_expected_action_and_return(no_param_action_one, NULL, 0, NULL, NULL);
    costumes_add_expected_action_and_return(no_param_action_two, NULL, 0, NULL, NULL);

    TEST_ASSERT_TRUE(costumes_is_action_expected(no_param_action_one, NULL, NULL, &retval_ptr));
}

TEST(costumes, actions_with_parameters_find_correct_action)
{
    int expected_retval = EXPECTED_RETVAL;
    void *retval_ptr;
    int_action_parameter_type_t expected_parameters;

    costumes_add_expected_action_and_return(int_parameter_action, NULL, 0, create_int_parameters(1), NULL);
    costumes_add_expected_action_and_return(int_parameter_action, NULL, 0, create_int_parameters(2), NULL);
    expected_parameters.value = 2;

    TEST_ASSERT_TRUE(costumes_is_action_expected(int_parameter_action, int_parameter_comparator, &expected_parameters, &retval_ptr));
    //TEST_ASSERT_EQUAL_INT(2, ((int_action_parameter_type_t*)fetched_action->parameters)->value);
    //TEST_ASSERT_EQUAL_INT(1, fetched_action->used_times);
    TEST_FAIL_MESSAGE("Not correct");
}

TEST(costumes, actions_with_parameters_action_not_found)
{
    int_action_parameter_type_t expected_parameters;

    costumes_add_expected_action_and_return(int_parameter_action, NULL, 0, create_int_parameters(1), NULL);
    expected_parameters.value = 3;

    //TEST_ASSERT_NULL(costumes_is_action_expected(int_parameter_action, int_parameter_comparator, &expected_parameters));
    TEST_FAIL_MESSAGE("Not correct");
}

TEST(costumes, actions_with_parameters_find_exhaust_all_previous_actions_of_same_type)
{
    costumes_action_t* fetched_action;
    int_action_parameter_type_t expected_parameters;

    costumes_add_expected_action_and_return(int_parameter_action, NULL, 0, create_int_parameters(1), NULL);
    costumes_add_expected_action_and_return(int_parameter_action, NULL, 0, create_int_parameters(2), NULL);

    expected_parameters.value = 2;
    //(void*) costumes_is_action_expected(int_parameter_action, int_parameter_comparator, &expected_parameters, NULL);
    expected_parameters.value = 1;

    // The find off the second action exhausts the first action of the same type
    //TEST_ASSERT_NULL(costumes_is_action_expected(int_parameter_action, int_parameter_comparator, &expected_parameters));
    TEST_FAIL_MESSAGE("Not correct");
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
