#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <iostream>
#include <World.h>

TEST_CASE("NodeTest") {
    CHECK(true);
    World::Chunk chunk(2);
    
    chunk.exportPLY("test.ply");
    chunk.exportOBJ("test.obj", World::Chunk::Exportmods::posColor);
}
