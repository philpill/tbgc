#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "./core.c"

static int setup(void **state)
{
    return 0;
};

static int teardown(void **state)
{
    return 0;
};

static int system_setup(void **state)
{
    return 0;
};

// https://jagssoftware.wordpress.com/2018/02/20/cmocka-testing-framework-example/
// https://stackoverflow.com/a/50393456/3983822
int main(int argc, char *argv[])
{
    int system_tests_result = 0;
    const struct CMUnitTest system_tests[] =
        {
            cmocka_unit_test_setup(test_init, system_setup)
        };
        
    system_tests_result = cmocka_run_group_tests(system_tests, NULL, NULL);

    return system_tests_result;
}