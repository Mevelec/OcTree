#pragma once

#include <OcTree/OcTree.h>
#include "Voxel.h"

namespace World
{

    //--------------------------------------------------------------
    //                   PointCloud
    //--------------------------------------------------------------
    class Chunk : public DataStructs::OcTree<Voxel>
    {
        public:
            Chunk(int size);
            ~Chunk();

            void exportPLY(const char* path);

            enum Exportmods {
                posColor = 0,
                voxelColor = 1
            };
            void exportOBJ(const char* path, Exportmods mod = Exportmods::voxelColor);
    };

} // namespace PointCloudExport
