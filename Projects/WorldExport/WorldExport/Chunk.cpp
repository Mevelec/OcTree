#include "Chunk.h"
#include <fstream>
#include <iostream>

namespace World
{
    Chunk::Chunk(int size) :
        OcTree(size)
    {
    }
    
    Chunk::~Chunk()
    {
    }


    void createBox(std::ofstream& out, int pos[3], const float& size, int color[3], int offset) {
        /*
            y
            | z
            |/
            o ------x
        */
        /*
              7-------6
             / |     /|
            3--+----2 |
            | 4 ----+-5
            |/      |/
            0-------1
        */
        int verts[8][3] = {
            {-1, -1, -1}, // bottom left     front
            { 1, -1, -1}, // bottom right    front
            { 1,  1, -1}, // top    right    front
            {-1,  1, -1}, // top    left     front

            {-1, -1,  1}, // bottom left     back
            { 1, -1,  1}, // bottom right    back
            { 1,  1,  1}, // top    right    back
            {-1,  1,  1}, // top    left     back

        };

        int tris[12][3] = {
            // z-
            {0, 1, 2},
            {2, 3, 0},
            // z+
            {4, 7, 6},
            {6, 5, 4},
            // x-
            {4, 0, 3},
            {3, 7, 4},
            // x+
            {1, 5, 6},
            {6, 2, 1},
            // y-
            {0, 4, 5},
            {5, 1, 0},
            // y+
            {3, 2, 6},
            {6, 7, 3}
        };
        
        //write vertices
        for(size_t i = 0; i < 8; ++i){
            out << "v " << verts[i][0]*size + pos[0]*size*2
                << " "  << verts[i][1]*size + pos[1]*size*2
                << " "  << verts[i][2]*size + pos[2]*size*2
                << " "  << float(color[0])/255.0
                << " "  << float(color[1])/255.0
                << " "  << float(color[2])/255.0
                << "\n";
        }
        //write faces
        for(size_t i = 0; i < 12; ++i){
            out << "f " << tris[i][0]+1+offset << " " << tris[i][1]+1+offset << " " << tris[i][2]+1+offset << "\n";
        }
    }

    void Chunk::exportBuffer(int version){
        /*
        void CreateMeshSection_LinearColor
        (
            int32 SectionIndex,
            const TArray< FVector > & Vertices, <=> array[nbvertex * 3]
            const TArray< int32 > & Triangles, <=> array[nbtris * 3 (3 by face)]
            const TArray< FVector > & Normals, <=> array[nbvertex * 3]
            const TArray< FVector2D > & UV0, <=> array[nbvertex * 2]
            const TArray< FVector2D > & UV1, <=> array[nbvertex * 2]
            const TArray< FVector2D > & UV2, <=> array[nbvertex * 2]
            const TArray< FVector2D > & UV3, <=> array[nbvertex * 2]
            const TArray< FLinearColor > & VertexColors, <=> array[nbvertex * 4] : arbg
            const TArray< FProcMeshTangent > & Tangents, <=> array[nbvertex * 3]
            bool bCreateCollision
        ) 
        */
        float size = 0.5;
        for (pos[0] = 0; pos[0] < this->getDimention(); ++pos[0])
        {
            for (pos[1] = 0; pos[1] < this->getDimention(); pos[1]++)
            {
                for (pos[2] = 0; pos[2] < this->getDimention(); pos[2]++)
                {
                    color[0] = (pos[0] == 0)? 0 : 255.0/this->getDimention()*pos[0];
                    color[1] = (pos[1] == 0)? 0 : 255.0/this->getDimention()*pos[1];
                    color[2] = (pos[2] == 0)? 0 : 255.0/this->getDimention()*pos[2];
                    createBox(file, pos, size, color, offset*8);
                    offset++;
                }
            }
        }
    }

    void Chunk::exportOBJ(const char* path, Exportmods mod){
        std::ofstream file(path);
        float size = 0.5;
        
        if (file.is_open())
        {
            file << "o cube\n";

            int pos[3];
            int color[] = {0, 0, 0};
            std::cout<<"DIMM = "<<this->getDimention()<<std::endl;
            int offset = 0;
            for (pos[0] = 0; pos[0] < this->getDimention(); ++pos[0])
            {
                for (pos[1] = 0; pos[1] < this->getDimention(); pos[1]++)
                {
                    for (pos[2] = 0; pos[2] < this->getDimention(); pos[2]++)
                    {
                        if(mod == Exportmods::posColor)
                        {
                            color[0] = (pos[0] == 0)? 0 : 255.0/this->getDimention()*pos[0];
                            color[1] = (pos[1] == 0)? 0 : 255.0/this->getDimention()*pos[1];
                            color[2] = (pos[2] == 0)? 0 : 255.0/this->getDimention()*pos[2];
                            createBox(file, pos, size, color, offset*8);
                        }
                        else if(mod ==  Exportmods::voxelColor) {
                            switch (this->get(pos[0], pos[1], pos[2]).voxeltype)
                            {
                            case VoxelType::STONE :
                                color[0] = 125;
                                color[1] = 125;
                                color[2] = 125;
                                createBox(file, pos, size, color, offset*8);
                                break;
                            case VoxelType::AIR :
                                break;
                            default:
                                color[0] = 255;
                                color[1] = 0;
                                color[2] = 255;
                                createBox(file, pos, size, color, offset*8);
                                break;
                            }
                        }
                        offset++;
                    }
                }
            }
            
            file.close();
        }
        else {
            throw "Unable to open file";
        }
    }

    void Chunk::exportPLY(const char* path){
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
                        file << " "<<this->get(x, y, z).voxeltype<<"\n"; //value
                    }
                }
            }
            
            file.close();
        }
        else {
            throw "Unable to open file";
        }
    }
    
} // namespace PointCloudExport
