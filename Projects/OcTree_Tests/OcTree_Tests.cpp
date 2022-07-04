#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <OcTree.h>


TEST_CASE("testing the factorial function") {
    CHECK(OcTree::factorial(1) == 1);
    CHECK(OcTree::factorial(2) == 2);
    CHECK(OcTree::factorial(3) == 6);
    CHECK(OcTree::factorial(10) == 3628800);
}