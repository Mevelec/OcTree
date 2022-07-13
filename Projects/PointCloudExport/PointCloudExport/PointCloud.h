#pragma once

#include <OcTree/OcTree.h>

namespace PointCloud
{
    class PointCloud : public Chunk::OcTree<int>
    {
        public:
            PointCloud(int size);
            ~PointCloud();

            bool exportPLY(const char* path);
    };
} // namespace PointCloudExport
