#pragma once

#include <OcTree/OcTree.h>

namespace World
{
    
    //--------------------------------------------------------------
    //                   Voxel
    //--------------------------------------------------------------
    enum VoxelType {
        STONE = 1,
        DEFAULT = 0
    };

    class Voxel 
    {
        public :
            VoxelType voxeltype;
    };
    inline bool operator==(const Voxel& left, const Voxel& right) { return left.voxeltype == right.voxeltype; }
    inline bool operator!=(const Voxel& left, const Voxel& right) { return !(left == right); }

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
