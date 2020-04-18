#ifndef RENDER_HPP
#define RENDER_HPP

struct GLFWwindow;

namespace cog {

    class Obj;
    class Postprocessor;

    extern GLFWwindow* window;
    bool render_init (int width, int height);
    void render_cleanup();
    void render_update();
    void use_postprocessor(Postprocessor *post);
    void loadVoxObj (Obj& obj);

}

#endif