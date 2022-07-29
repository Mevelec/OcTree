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

            enum Exportmods {
                posColor = 0,
                voxelColor = 1
            };
            void exportPLY(const char* path);
            void exportOBJ(const char* path, Exportmods mod = Exportmods::voxelColor);
            void exportBuffer();
    };

} // namespace PointCloudExport
