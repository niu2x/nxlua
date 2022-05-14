#include "gfx.h"

#include <chrono>

#include "nxlua/nx_assert.h"
#include "niu2x/utils.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace nxlua::gfx {

static GLFWwindow* current_glfw_window = nullptr;
static double now_seconds = 0;

static void glfw_setup();
static void glfw_cleanup();

static GLFWwindow* create_glfw_window(const window_config_t& c);
static void destroy_glfw_window(GLFWwindow* window);

static void glfw_error_callback(int error, const char* description);

static void key_callback(
    GLFWwindow*, int key, int scancode, int action, int mods);
static void mouse_key_callback(GLFWwindow*, int key, int action, int mods);
static void framebuffer_size_callback(GLFWwindow*, int w, int h);
static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);

static void imgui_setup(GLFWwindow* window);
static void imgui_cleanup();
static void imgui_update(double dt);
static const window_config_t* get_window_option(GLFWwindow* window);

void run(const window_config_t& c)
{
    NX_ASSERT(current_glfw_window == nullptr, "already had a glfw_window.");

    glfw_setup();

    auto glfw_window = create_glfw_window(c);
    current_glfw_window = glfw_window;

    glfwSetWindowUserPointer(glfw_window, (void*)&c);

    glfwSetKeyCallback(glfw_window, key_callback);
    glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);
    glfwSetCursorPosCallback(glfw_window, cursor_pos_callback);
    glfwSetMouseButtonCallback(glfw_window, mouse_key_callback);

    auto last_now = std::chrono::steady_clock::now();
    auto now = last_now;
    float dt = 0;

    auto update = c.update;

    imgui_setup(glfw_window);

    if (c.setup)
        c.setup();

#define duration_cast(t)                                                       \
    std::chrono::duration_cast<std::chrono::microseconds>((t))

    static double average_dt = 1 / 60.0;
    static double scale = 1 / 1000000.0;
    while (!glfwWindowShouldClose(glfw_window)) {
        now = std::chrono::steady_clock::now();
        dt = duration_cast(now - last_now).count() * scale;
        last_now = now;

        now_seconds = duration_cast(now.time_since_epoch()).count() * scale;

        glfwPollEvents();

        update(dt);

        glClear(
            GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        imgui_update(dt);

        average_dt = average_dt * 0.99 + dt * 0.01;
        glfwSwapBuffers(glfw_window);
    }

    if (c.cleanup)
        c.cleanup();

    imgui_cleanup();

    current_glfw_window = nullptr;
    destroy_glfw_window(glfw_window);

    glfw_cleanup();
}

static void glfw_setup()
{
    glfwSetErrorCallback(glfw_error_callback);
    auto r = glfwInit();
    NX_ASSERT(r, "glfw init failed");
}

static void glfw_cleanup() { glfwTerminate(); }

static void glfw_error_callback(int error, const char* description)
{
    NX_LOG_E("Glfw Error %d: %s\n", error, description);
}

static GLFWwindow* create_glfw_window(const window_config_t& c)
{
    if (c.options & MSAA)
        glfwWindowHint(GLFW_SAMPLES, 8);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    auto glfw_window
        = glfwCreateWindow(c.width, c.height, c.title.c_str(), 0, nullptr);
    NX_ASSERT(glfw_window, "create glfw_window failed.");

    glfwMakeContextCurrent(glfw_window);
    glfwSwapInterval(1);
    NX_ASSERT(glewInit() == GLEW_OK, "glew init failed");

    return glfw_window;
}

static void destroy_glfw_window(GLFWwindow* glfw_window)
{
    glfwDestroyWindow(glfw_window);
}

static void key_callback(
    GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // NX_LOG_D("%d %d %d %d", key, scancode, action, mods);
    nx::unused(scancode);
    auto* c = get_window_option(window);
    if (c && c->key_callback) {
        c->key_callback(key, action, mods);
    }
}

static void mouse_key_callback(
    GLFWwindow* window, int key, int action, int mods)
{
    // NX_LOG_D("%d %d %d", key, action, mods);
    auto* c = get_window_option(window);
    if (c && c->key_callback) {
        c->key_callback(key, action, mods);
    }
}

static const window_config_t* get_window_option(GLFWwindow* window)
{
    void* ud = glfwGetWindowUserPointer(window);
    if (ud) {
        const window_config_t* c = reinterpret_cast<const window_config_t*>(ud);
        return c;
    } else
        return nullptr;
}

static void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
    auto* c = get_window_option(window);
    if (c) {
        double scale = std::min(double(w) / c->width, double(h) / c->height);
        int viewport_width = scale * c->width;
        int viewport_height = scale * c->height;
        int viewport_x = (w - viewport_width) >> 1;
        int viewport_y = (h - viewport_height) >> 1;

        glViewport(viewport_x, viewport_y, viewport_width, viewport_height);
    }
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    auto* c = get_window_option(window);
    if (c && c->mouse_pos_callback) {
        c->mouse_pos_callback(xpos, ypos);
    }
}

static void imgui_setup(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char* glsl_version = "#version 130";
    ImGui_ImplOpenGL3_Init(glsl_version);
}

static void imgui_cleanup()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

static void imgui_update(double dt)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();

    ImGui::LabelText("FPS", "%d", (int)(1 / dt));
    ImGui::LabelText("dt", "%.4f", dt);

    ImGui::EndFrame();

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void exit()
{
    NX_ASSERT(current_glfw_window != nullptr, "no glfw_window.");
    glfwSetWindowShouldClose(current_glfw_window, GLFW_TRUE);
}

} // namespace nxlua::gfx