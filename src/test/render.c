#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../render.h"

static void test_render_add_new_component(void** state) {
    int index = render_add_new_component("test1");
    assert_int_equal(index, 1);
    index = render_add_new_component("test2");
    assert_int_equal(index, 2);
    RenderComponent *components = render_get_components();
    assert_string_equal(components[0].path, "test1");
    assert_string_equal(components[1].path, "test2");
    index = render_add_new_component("test3");
    index = render_add_new_component("test4");
    index = render_add_new_component("test5");
    index = render_add_new_component("test6");
    index = render_add_new_component("test7");
    index = render_add_new_component("test8");
    index = render_add_new_component("test9");
    index = render_add_new_component("test10");
    index = render_add_new_component("test11");
    assert_int_equal(index, 11);
}

static void test_render_get_component_by_path(void** state) {
    render_add_new_component("test1");
    render_add_new_component("test2");
    render_add_new_component("test3");
    RenderComponent *component = render_get_component_by_path("test2");
    assert_string_equal(component->path, "test2");
}

static void test_render_get_component_by_index(void** state) {
    render_add_new_component("test1");
    render_add_new_component("test2");
    render_add_new_component("test3");
    RenderComponent *component = render_get_component_by_index(2);
    assert_string_equal(component->path, "test3");
}

static void test_render_remove_component(void** state) {
    render_add_new_component("test1");
    render_add_new_component("test2");
    render_add_new_component("test3");
    RenderComponent *component = render_get_component_by_path("test2");
    RenderComponent **ptr = &component;
    render_remove_component(ptr);
    assert_null(component);
    component = render_get_component_by_index(0);
    assert_non_null(component);
    component = render_get_component_by_index(1);
    assert_null(component);
    component = render_get_component_by_index(2);
    assert_non_null(component);
}

static void test_render_remove_component_by_index(void** state) {
    render_add_new_component("test1");
    render_add_new_component("test2");
    render_add_new_component("test3");
    render_remove_component_by_index(1);
    RenderComponent *component = render_get_component_by_index(0);
    assert_non_null(component);
    component = render_get_component_by_index(1);
    assert_null(component);
    component = render_get_component_by_index(2);
    assert_non_null(component);
}