#pragma once

#include <OcTree/OcTree.h>

namespace PointCloud
{
    class PointCloud : public Chunk::OcTree<int>
    {
        public:
            PointCloud(int size);
            ~PointCloud();

            void exportPLY(const char* path);
            void exportOBJ(const char* path);

    };
} // namespace PointCloudExport
