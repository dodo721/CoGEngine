#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "obj.hpp"

namespace cog {

    class Camera : Obj {}

        public:
            float horizontalAngle = 3.14f;
            float verticalAngle = 0.0f;
            float FoV = 45.0f;
            void cam_update();
    }

}

#endif