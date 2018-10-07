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

/*
 * Tests to be written:
 * - TBD
 */

TEST_GROUP(costumes);
TEST_GROUP_RUNNER(costumes)
{
    RUN_TEST_CASE(costumes, init);
}

TEST_SETUP(costumes)
{
    schedule_init();
}

TEST_TEAR_DOWN(costumes)
{
}

/*
 * TEST CASES
 */
TEST(costumes, init)
{
    TEST_FAIL_MESSAGE("Not implemented");
}
