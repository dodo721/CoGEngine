#ifndef RENDER_HPP
#define RENDER_HPP

struct GLFWwindow;

namespace cog {

    class Obj;

    extern GLFWwindow* window;
    bool render_init (int width, int height);
    void render_cleanup();
    void render_update();
    void loadVoxObj (Obj& obj);

}

#endif