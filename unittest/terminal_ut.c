/*

 */

#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include "terminals.h"

terminal terminals[MAX_TERMINALS];

/* The suite initialization function.

 */
int init_suite1(void)
{
      return 0;
}

/* The suite cleanup function.
 */
int clean_suite1(void)
{
      return 0;
}

/* 
 * get_free_terminal, return the id of unused terminal
 * return -1 if there is no unused termial
 * return -1 when the terminal array point is NULL
 */
void test_get_free_terminal(void)
{
   CU_ASSERT(-1 == get_free_terminal(NULL));
   CU_ASSERT(0 == get_free_terminal(terminals));
   for (int i=0; i<MAX_TERMINALS; i++) {
      terminals[i].used = 1;
   }
   CU_ASSERT(-1 == get_free_terminal(terminals));
   for (int i=0; i<MAX_TERMINALS; i++) {
      terminals[i].used = 0;
   }
}

void test_update_terminal_attribute(void)
{
   char attribute[MAX_ATTRIBUTES_LEN+1];
   CU_ASSERT(-1 == update_terminal_attribute(NULL, 0, attribute));
   CU_ASSERT(-1 == update_terminal_attribute(terminals, -1, NULL));
   CU_ASSERT(-1 == update_terminal_attribute(terminals, MAX_TERMINALS, NULL));
   CU_ASSERT(-1 == update_terminal_attribute(terminals, 1, NULL));
   memset(attribute,'a',MAX_ATTRIBUTES_LEN);
   attribute[MAX_ATTRIBUTES_LEN] = 0;
   CU_ASSERT(-1 == update_terminal_attribute(terminals, 1, attribute));
   attribute[MAX_ATTRIBUTES_LEN-1] = 0;
   CU_ASSERT(0 == update_terminal_attribute(terminals, 1, attribute));
   memset(terminals, 0, sizeof(terminals));
}


void test_get_terminal_attribute(void)
{
   CU_ASSERT_PTR_NULL(get_terminal_attribute(NULL, 0));
   CU_ASSERT_PTR_NULL(get_terminal_attribute(terminals, -1));
   CU_ASSERT_PTR_NULL(get_terminal_attribute(terminals, MAX_TERMINALS));
   CU_ASSERT_PTR_NULL(get_terminal_attribute(terminals, 1));
   terminals[1].used = 1;
   memset(terminals[1].attributes_str, 'a', 3);
   CU_ASSERT_STRING_EQUAL("aaa", get_terminal_attribute(terminals, 1));
   memset(terminals, 0, sizeof(terminals));
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   CU_TestInfo test_array1[] = {
      { "test of get_free_terminal()", test_get_free_terminal},
      { "test of update_terminal_attribute()", test_update_terminal_attribute},
      { "test of get_terminal_attribute()", test_get_terminal_attribute},
      CU_TEST_INFO_NULL,
   };

   CU_SuiteInfo suites[] = {
      { "Terminal_Suite_1", init_suite1, clean_suite1, NULL, NULL,test_array1 },
      CU_SUITE_INFO_NULL,
   };

   CU_ErrorCode error = CU_register_suites(suites);
   if (CUE_SUCCESS != error)
   {
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}

