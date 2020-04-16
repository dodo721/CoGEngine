#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "voxobj.hpp"

namespace vox::obj {

    class Camera : VoxObj {

        public:
            float horizontalAngle = 3.14f;
            float verticalAngle = 0.0f;
            float FoV = 45.0f;
            void cam_update();
    }

}

#endif