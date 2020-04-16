#ifndef VOXMESH_HPP
#define VOXMESH_HPP

#include "mesh.hpp"
typedef unsigned int Voxuint;

namespace vox::obj {

    class VoxMesh : public Mesh {
        bool*** data;
        Voxuint width = 0;
        Voxuint height = 0;
        Voxuint length = 0;
        void calcMesh ();
        enum FaceDirection {Up, Down, Left, Right, Forward, Backward};
        float* getFaceVerts (FaceDirection direction);
        void addFace (FaceDirection direction);
        struct VoxUnitStack;
        VoxUnitStack* topUnit = NULL;
        bool popUnitStack ();
        void pushUnitStack (Voxuint x, Voxuint y, Voxuint z);
        public:
            bool extendable = false;
            VoxMesh();
            VoxMesh(bool*** data, Voxuint width, Voxuint height, Voxuint length);
            ~VoxMesh();
            bool appendUnit (Voxuint x, Voxuint y, Voxuint z);
    };

}

#endif