/*
 * BitLoom Costumes - A simple mocking framework for Bitloom projects
 *
 * Copyright (c) 2016-2018. BlueZephyr
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include <stdlib.h>
#include <unity.h>
#include <stdbool.h>
#include <costumes.h>

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
void costumes_init(void)
{
    self.expected_actions = calloc(MAX_NO_OF_EXPECTED_ACTIONS, sizeof(costumes_action_t));
    self.no_of_stored_actions = 0;
}

void costumes_add_expected_action(costumes_action_t action)
{
    fail_when(too_many_expectations(), string_too_many_expectations);
    self.expected_actions[self.no_of_stored_actions++] = action;
}

costumes_action_t* costumes_find_action(costumes_action_type_t type, void *parameters)
{
    int i;

    for(i=0; i<self.no_of_stored_actions; i++)
    {
       if (self.expected_actions[i].type == type)
       {
           return &(self.expected_actions[i]);
       }
    }

    return NULL;
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
