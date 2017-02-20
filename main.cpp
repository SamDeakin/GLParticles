#include <iostream>
#include <string>

#include <GL/glew.h>

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
    cout << internal_width << " x " << internal_height << " window: " << window_width << " x " << window_height << endl;

    glewExperimental = GL_TRUE;
    glfwMakeContextCurrent(window);
    glewInit();

    glfwSetKeyCallback(window, key_callback);
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window)) {
        render(window);

        // Update internal size
        glfwGetFramebufferSize(window, &internal_width, &internal_height);
        glfwGetWindowSize(window, &window_width, &window_height);
        cout << internal_width << " x " << internal_height << " window: " << window_width << " x " << window_height << endl;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
