#ifndef RENDER_HPP
#define RENDER_HPP

struct GLFWwindow;

namespace vox::obj {
    class VoxObj;
}

namespace vox::render {

    extern GLFWwindow* window;
    bool render_init (int width, int height);
    void render_cleanup();
    void render_update();
    void loadVoxObj (vox::obj::VoxObj& obj);

}

#endif