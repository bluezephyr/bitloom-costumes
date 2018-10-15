/*
 * BitLoom Costumes - A simple mocking framework for Bitloom projects
 *
 * Main file for the unit tests.
 *
 * Copyright (c) 2018 BlueZephyr
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "unity_fixture.h"

static void run_tests(void)
{
    RUN_TEST_GROUP(costumes);
}

int main(int argc, const char* argv[])
{
    return UnityMain(argc, argv, run_tests);
}
