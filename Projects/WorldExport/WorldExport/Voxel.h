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
};