#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <iostream>
#include <PointCloud.h>

TEST_CASE("NodeTest") {
    CHECK(true);
    PointCloud::PointCloud pointCloud(2);

    int k = 0;
    for(int x = 0; x < pointCloud.getDimention(); ++x){
        for(int y = 0; y < pointCloud.getDimention(); ++y){
            for(int z = 0; z < pointCloud.getDimention(); ++z){
                pointCloud.set(k, x, y, z);
                CHECK(pointCloud.get(x, y, z) == k);
                k++;
            }
        }
    }

    pointCloud.exportPLY("test.ply");
    pointCloud.exportOBJ("test.obj");
}
