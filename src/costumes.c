/*
 * BitLoom Costumes - A simple mocking framework for Bitloom projects
 *
 * Copyright (c) 2018. BlueZephyr
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include <unity_fixture.h>
#include <stdbool.h>
#include "costumes.h"

/*
 * Costumes class to hold state and expected operations (singleton)
 * A single object self is declared statically.
 */
typedef struct
{
    costumes_action_t* expected_actions;
    int no_of_stored_actions;
} costumes_t;
static costumes_t self;


/* Strings */
static const char* string_too_many_expectations = "Too many expectations, adjust MAX_NO_OF_EXPECTED_ACTIONS";


/********************************************************************
 * Local function prototypes
 ********************************************************************/
static void fail_when(int condition, const char* message);
static bool too_many_expectations(void);


/********************************************************************
 * Public function implementations
 ********************************************************************/
void costumes_create(void)
{
    self.expected_actions = calloc(MAX_NO_OF_EXPECTED_ACTIONS, sizeof(costumes_action_t));
    self.no_of_stored_actions = 0;
}

void costumes_destroy(void)
{
    int i;
    for (i=0; i < self.no_of_stored_actions; i++)
    {
        free(self.expected_actions[i].parameters);
    }
    free(self.expected_actions);
}

/*
 * Add an expected action.
 * The max_usage parameter specifies the maximum number of times the action
 * may be used.  0 to specify no limit.
 */
void costumes_add_expected_action(costumes_action_type_t type, unsigned int max_usage, void *parameters)
{
    fail_when(too_many_expectations(), string_too_many_expectations);

    self.expected_actions[self.no_of_stored_actions].type = type;
    self.expected_actions[self.no_of_stored_actions].max_usage = max_usage;
    self.expected_actions[self.no_of_stored_actions].used_times = 0;
    self.expected_actions[self.no_of_stored_actions].exhausted = false;
    self.expected_actions[self.no_of_stored_actions].parameters = parameters;
    self.no_of_stored_actions++;
}

costumes_action_t* costumes_find_action(costumes_action_type_t type, compare_parameters_func_t *compare_parameters,
                                        void *parameters)
{
    int i;
    costumes_action_t* action;

    for(i=0; i<self.no_of_stored_actions; i++)
    {
        action = &self.expected_actions[i];

        if ((action->type == type) && (!action->exhausted))
        {
            if (compare_parameters != NULL)
            {
                if (compare_parameters(action->parameters, parameters))
                {
                    // Found
                    break;
                }
                else
                {
                    // Found an action of the correct type but with wrong parameters
                    // This should make the action exhausted.
                    action->exhausted = true;
                }
            }
            else
            {
                // Found
                break;
            }
        }
        action = NULL;
    }

    if (action != NULL)
    {
        action->used_times++;
        if (action->used_times == action->max_usage)
        {
            action->exhausted = true;
        }
        return action;
    }
    else
    {
        return NULL;
    }
}

/********************************************************************
 * Local function implementations
 ********************************************************************/
static void fail_when(int condition, const char *message)
{
    if (condition)
    {
        TEST_FAIL_MESSAGE(message);
    }
}

static bool too_many_expectations(void)
{
    if (self.no_of_stored_actions == MAX_NO_OF_EXPECTED_ACTIONS)
    {
        return true;
    }
    else
    {
        return false;
    }
}
