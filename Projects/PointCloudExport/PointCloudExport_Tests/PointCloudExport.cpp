#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <iostream>
#include <PointCloud.h>

TEST_CASE("NodeTest") {
    CHECK(true);
    PointCloud::PointCloud pointCloud(2);
    
    pointCloud.exportPLY("test.ply");
    pointCloud.exportOBJ("test.obj", PointCloud::PointCloud::Exportmods::posColor);
}
