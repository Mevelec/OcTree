#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <OcTree/OcTree.h>
#include <iostream>



TEST_CASE("OctreeTest") {

    SUBCASE("OcTree::OcTree(x)") {
        for(int i = 0; i < 10; ++i){
            Chunk::OcTree<int> octree(i);
            CHECK(octree.getDepth() == i);
            CHECK(octree.getDimention() == pow(2, i));
        }
    }

    SUBCASE("OcTree::get(x)") {
        Chunk::OcTree<int> octree(1);
        CHECK(octree.getDepth() == 1);
        CHECK(octree.getDimention() == 2);

        for(int x = 0; x < octree.getDimention(); ++x){
            CHECK(x < octree.getDimention());
            for(int y = 0; y < octree.getDimention(); ++y){
                for(int z = 0; z < octree.getDimention(); ++z){
                    CHECK(x < octree.getDimention());
                    CHECK(y < octree.getDimention());
                    CHECK(y < octree.getDimention());

                    CHECK(octree.get(x, y, z) == 0);
                }
            }
        }
    }

    SUBCASE("OcTree::set()") {
        for(int i = 1; i < 2; ++i){
            Chunk::OcTree<int> octree(i);
            CHECK(octree.getDepth() == i);
            CHECK(octree.getDimention() == pow(2, i));

            int k = 0;
            for(int x = 0; x < octree.getDimention(); ++x){
                for(int y = 0; y < octree.getDimention(); ++y){
                    for(int z = 0; z < octree.getDimention(); ++z){
                        octree.set(k, x, y, z);
                        CHECK(octree.get(x, y, z) == k);
                        k++;
                    }
                }
            }
            k = 0;
            for(int x = 0; x < octree.getDimention(); ++x){
                for(int y = 0; y < octree.getDimention(); ++y){
                     for(int z = 0; z < octree.getDimention(); ++z){
                        CHECK(octree.get(x, y, z) == k);
                        k++;
                    }
                }
            }
        }
    }
}

/*
## tests

tester chunk de taille 0
tester chunk taille fixe
tester chunk taille variable
tester diviser plus
tester reduction 
*/