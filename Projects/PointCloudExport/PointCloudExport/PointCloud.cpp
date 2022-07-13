#include "PointCloud.h"
#include <fstream>

namespace PointCloud
{
    PointCloud::PointCloud(int size) :
        OcTree(size)
    {
    }
    
    PointCloud::~PointCloud()
    {
    }

    bool PointCloud::exportPLY(const char* path){
        std::ofstream file(path);
        if (file.is_open())
        {
            file << "ply\n";
            file << "format ascii 1.0\n";
            file << "element vertex 8\n"; //number of vertices
            file << "property float32 x\n"; //define property x
            file << "property float32 y\n"; //define property x
            file << "property float32 z\n"; //define property x
            file << "property float32 integer\n"; //define property x
            file << "end_header\n"; //define property x

            for (size_t x = 0; x < this->getDimention(); x++)
            {
                for (size_t y = 0; y < this->getDimention(); y++)
                {
                    for (size_t z = 0; z < this->getDimention(); z++)
                    {
                        file << x <<" "<< y <<" "<< z; //pos
                        file << " "<<this->get(x, y, z)<<"\n"; //value
                    }
                }
            }
            
            file.close();
        }
        else {
            throw "Unable to open file";
        }
        return 0;
    }
    
} // namespace PointCloudExport
