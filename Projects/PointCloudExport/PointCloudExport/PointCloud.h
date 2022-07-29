#pragma once

#include <OcTree/OcTree.h>

namespace PointCloud
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
    class PointCloud : public Chunk::OcTree<Voxel>
    {
        public:
            PointCloud(int size);
            ~PointCloud();

            void exportPLY(const char* path);
            void exportOBJ(const char* path);
    };

} // namespace PointCloudExport
