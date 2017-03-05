#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

#include "definitions.hpp"
#include "camera.hpp"

Camera::Camera(
    float fovy, float width, float height, float near, float far) :
    base_V(glm::mat4()), x(0), y(0), z_offset(2), rot_horizontal(0), rot_vertical(0) {
    setPerspectiveMatrix(fovy, width, height, near, far);
}

void Camera::logic() {
    // We have to transform the camera to look in the right direction
    // Then we can move based on that transform
}

void Camera::setPerspectiveMatrix(float fovy, float width, float height, float near, float far) {
    P = glm::perspectiveFov(fovy, width, height, near, far);
}

glm::mat4 Camera::getPerspectiveMatrix() {
    return P;
}

glm::mat4 Camera::getViewMatrix() {
    // Create a view matrix based on the the position followed by the rotation
    glm::vec3 eye = getPlayerPosition();

    glm::vec3 centre = glm::vec3(0.0, 1.0, 0.0); // Starting looking position
    centre = glm::rotate(centre, float(rot_vertical), glm::vec3(1.0, 0.0, 0.0));
    centre = glm::rotate(centre, float(rot_horizontal), glm::vec3(0.0, 0.0, 1.0));
    centre = centre + eye;

    return glm::lookAt(eye, centre, canonicalUpVector);
}

glm::vec3 Camera::getPlayerPosition() {
    return glm::vec3(x, y, z_offset);
}

void Camera::mouseMoved(double xPos, double yPos) {
    double dx = xPos - mouse_x;
    double dy = yPos - mouse_y;

    dx *= lookSensitivity;
    dy *= lookSensitivity;

    std::cout << "Rotate: " << dx << " " << dy << std::endl;

    mouse_x = xPos;
    mouse_y = yPos;
}

void Camera::keyPressed(int key) {

}

void Camera::keyReleased(int key) {

}
