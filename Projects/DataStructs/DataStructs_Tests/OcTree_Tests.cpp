#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <OcTree/OcTree.h>
#include <iostream>

TEST_CASE("NodeTest") {

    DataStructs::Node<int> node(1);
    SUBCASE("Test constructor") {
        CHECK(node.data() == 1);
        CHECK(node.childs() == nullptr);
        CHECK(node.needReduce() == false);
    }
    
    SUBCASE("Test split and reduce") {
        node.split();

        CHECK(node.needReduce() == true);
        CHECK(node.childs()[0].data() == 1);

        node.childs()[0].set(2);
        CHECK(node.needReduce() == false);

        node.reduce();
        CHECK(node.needReduce() == false);

        node.childs()[0].set(1);
        CHECK(node.needReduce() == true);

        node.reduce();
        CHECK(node.needReduce() == false);
        CHECK(node.data() == 1);
        CHECK(node.childs() == nullptr);
        CHECK(node.needReduce() == false);
    }
}

TEST_CASE("OctreeTest") {

    SUBCASE("Test constructor") {
        for(int i = 0; i < 10; ++i){
            DataStructs::OcTree<int> octree(i);
            CHECK(octree.getDepth() == i);
            CHECK(octree.getDimention() == pow(2, i));
        }
    }

    SUBCASE("Test Getter simple") {
        DataStructs::OcTree<int> octree(1);
        CHECK(octree.getDepth() == 1);
        CHECK(octree.getDimention() == 2);

        for(int x = 0; x < octree.getDimention(); ++x){
            CHECK(x < octree.getDimention());
            for(int y = 0; y < octree.getDimention(); ++y){
                for(int z = 0; z < octree.getDimention(); ++z){
                    CHECK(x < octree.getDimention());
                    CHECK(y < octree.getDimention());
                    CHECK(y < octree.getDimention());
                    {
                        CHECK(octree.get(x, y, z) == 0);
                    }
                }
            }
        }
    }

    SUBCASE("Test cases") {
        for(int i = 1; i < 2; ++i){
            DataStructs::OcTree<int> octree(i);
            SUBCASE("Test init") {
                CHECK(octree.getDepth() == i);
                CHECK(octree.getDimention() == pow(2, i));
            }

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

            SUBCASE("Test get setted") {
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
}

/*
## tests

tester DataStructs de taille 0
tester DataStructs taille fixe
tester DataStructs taille variable
tester diviser plus
tester reduction 
*/