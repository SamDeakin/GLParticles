#pragma once

/*
 * This class manages the camera and player location.
 * We cache things such as the P matrix.
 * Others like the V matrix are recreated each frame to allow easy restrictions
 * on how the player can move. These restrictions are mainly not being about to
 * look absolutely up or down and moving only across the ground.
 */

#include <glm/glm.hpp>

class Camera {
public:
    Camera(float fovy, float width, float height, float near, float far);

    // Perform frame logic, mostly moving the camera
    void logic();

    glm::mat4 getPerspectiveMatrix();
    glm::mat4 getViewMatrix();
    glm::vec3 getPlayerPosition();
    glm::vec3 getPlayerLookDirection();

    void setPerspectiveMatrix(float fovy, float width, float height, float near, float far);

    void mouseMoved(double xPos, double yPos);
    void keyPressed(int key);
    void keyReleased(int key);
private:
    // We save the mouse position too for stuff
    double mouse_x;
    double mouse_y;

    // We save the currently held buttons too
    bool key_w;
    bool key_s;
    bool key_a;
    bool key_d;
    bool key_shift;

    // Saved perspective matrix
    glm::mat4 P;

    // Base transform matrix for the view
    glm::mat4 base_V;

    /*
     * We store the player's position as an x and y value because these can change
     * The player's z value is a separate offset because the player shouldn't be
     * moving up and down.
     */
    double x;
    double y;
    double z_offset;

    /*
     * The player's rotations are stored as two angles.
     * We shouldn't encounter gimbal lock because of the restrictions placed on them.
     * Mainly the player can't rotate on their forward axis and also cannot look
     * directly up or directly down.
     * Both of the rotation axes are also always orthogonal.
     */
    double rot_horizontal;
    double rot_vertical;
};
