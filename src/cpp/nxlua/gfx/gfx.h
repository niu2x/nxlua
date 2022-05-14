#ifndef NXLUA_GFX_GFX_H
#define NXLUA_GFX_GFX_H

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace nxlua::gfx {

enum window_option_constant {
    MSAA = 1 << 0,
};

struct window_config_t {
    std::string title;
    int width, height;
    uint64_t options;
    void (*update)(double);
    void (*setup)();
    void (*cleanup)();
    void (*key_callback)(int keycode, int action, int mods);
    void (*mouse_pos_callback)(double xpos, double ypos);
};

void run(const window_config_t& c);
void exit();

} // namespace nxlua::gfx

#endif