namespace World
{
    //--------------------------------------------------------------
    //                   Voxel
    //--------------------------------------------------------------
    enum VoxelType {
        AIR = 0,
        STONE = 1,
    };

    class Voxel 
    {
        public :
            VoxelType voxeltype;
    };

    inline bool operator==(const Voxel& left, const Voxel& right) { return left.voxeltype == right.voxeltype; }
    inline bool operator!=(const Voxel& left, const Voxel& right) { return !(left == right); }
};