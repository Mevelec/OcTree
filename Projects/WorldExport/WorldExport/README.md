## Export Point cloud
https://en.wikipedia.org/wiki/PLY_(file_format)

https://3dviewer.net/

https://sites.google.com/site/letsmakeavoxelengine/home/landcape-creation

```
ply
format ascii 1.0           { ascii/binary, format version number }
comment made by anonymous  { comments are keyword specified }
comment this file is a cube
element vertex 8           { define "vertex" element, 8 in file }
property float32 x         { vertex contains float "x" coordinate }
property float32 y         { y coordinate is also a vertex property }
property float32 z         { z coordinate, too }
element face 6             { there are 6 "face" elements in the file }
property list uint8 int32 vertex_index
                            { "vertex_indices" is a list of ints }
end_header                 { delimits the end of the header }
0 0 0                      { start of vertex list }
0 0 1
0 1 1
0 1 0
1 0 0
1 0 1
1 1 1
1 1 0
4 0 1 2 3                  { start of face list }
4 7 6 5 4
4 0 4 5 1
4 1 5 6 2
4 2 6 7 3
```