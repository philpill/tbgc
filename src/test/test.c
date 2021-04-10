#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "./core.c"
#include "./render.c"

static int setup(void **state)
{
    render_clear_components();
    return 0;
};

static int teardown(void **state)
{
    return 0;
};

// https://jagssoftware.wordpress.com/2018/02/20/cmocka-testing-framework-example/
// https://stackoverflow.com/a/50393456/3983822
int main(int argc, char *argv[])
{
    const struct CMUnitTest tests[] =
        {
            cmocka_unit_test(test_init),
            cmocka_unit_test_setup(test_render_add_new_component, setup),
            cmocka_unit_test_setup(test_render_get_component_by_path, setup),
            cmocka_unit_test_setup(test_render_get_component_by_index, setup),
            cmocka_unit_test_setup(test_render_remove_component, setup),
            cmocka_unit_test_setup(test_render_remove_component_by_index, setup),
        };

    return cmocka_run_group_tests(tests, NULL, NULL);
}