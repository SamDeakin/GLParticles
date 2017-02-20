#include <iostream>
#include <string>

#include <GL/gl3w.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;
using namespace std;

#define GLSL(src) #src

static void error_callback(int error, const char *description) {
    fputs(description, stderr);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

static void render(GLFWwindow *window) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Get camera specifics
    // TODO

    // Draw skybox
    // nice-to-have TODO

    // Draw ground
    // TODO

    // Draw pixels
    // TODO
}

static void logic() {
    // Move Camera based on held buttons
    // TODO

    // Move Particles based on player position and their velocities
    // TODO
}

int main(void) {
    GLFWwindow *window;
    GLFWmonitor *monitor;
    int window_width = 1280;
    int window_height = 720;
    int internal_width = 0;
    int internal_height = 0;
    string title = "Particles";

    glfwSetErrorCallback(error_callback);

    if (glfwInit() == GL_FALSE) {
        fprintf(stderr, "Error calling glfwInit.\n");
        std::abort();
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 0);
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);

    monitor = glfwGetPrimaryMonitor();
    if (monitor == NULL) {
        glfwTerminate();
        fprintf(stderr, "Error calling glfwGetPrimaryMonitor.\n");
        abort();
    }

    window = glfwCreateWindow(window_width, window_height, title.c_str(), NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        fprintf(stderr, "Error calling glfwCreateWindow.\n");
        abort();
    }

    // Update internal size
    glfwGetFramebufferSize(window, &internal_width, &internal_height);
    glfwGetWindowSize(window, &window_width, &window_height);

    int x, y;
    const GLFWvidmode *video_mode = glfwGetVideoMode(monitor);
    x = video_mode->width;
    y = video_mode->height;

    x = (x - window_width) / 2;
    y = (y - window_height) / 2;

    glfwSetWindowPos(window, x, y);

    glfwMakeContextCurrent(window);
    gl3wInit();

    glfwSetKeyCallback(window, key_callback);
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // This should throttle our updates to 60fps
    // Lets hope the comp can keep up LOL
    glfwSwapInterval(1);

    // Render only the front face of geometry.
    // TODO reenable this after other renderings work
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    // Setup  some initial OpenGL stuff
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
    glEnable(GL_DEPTH_CLAMP);

    glClearDepth(1.0f);
    glClearColor(0.3, 0.5, 0.7, 1.0);

    // Set up objects
    // TODO initialize camera
    // TODO initialize ground
    // nice-to-have TODO initialize skybox
    // TODO initialize particles

    while (!glfwWindowShouldClose(window)) {
        // React to events
        glfwPollEvents();

        // Update sizes in case of change
        // Needed because FB can resize when changing monitors
        glfwGetFramebufferSize(window, &internal_width, &internal_height);
        // Not needed because window can't change virtual size
        // glfwGetWindowSize(window, &window_width, &window_height);

        // Perform calculations based on inputs
        logic();

        // Draw stuff
        render(window);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
