#pragma once

/*
 * This class handles drawing of the ground.
 * It should be given a position then draw a flat ground at that position extending out of view.
 * This is so the ground appears infinite. We don't actually care about the ground.
 *
 * TODO use a texture and modifying the uv coords to give illusion of moving accross ground
 * This will require a properly tessellating ground texture. Try hexagons or triangles, they'll look cool.
 */

#include <glm/glm.hpp>
#include <GL/gl3w.h>

class Ground {
public:
    Ground();
    ~Ground();
    /*
     * Call this method to render the ground to screen
     * This takes the players current position so it can place a flat ground centred under the player.
     */
    void render(glm::vec3 player, glm::mat4 PV);

    /*
     * This method is called by render
     * Call this to trigger just the uploading of M and drawing of geometry
     */
    void drawCall(glm::vec3 player, GLint M_location);
private:

};
