#include "definitions.hpp"
#include "ground.hpp"

using namespace glm;

/*
 * Just static data for the quad to be rendered
 */
GLFloat raw_vertices[] = {
    1.0, 1.0, 0.0,
    -1.0, 1.0, 0.0,
    -1.0, -1.0, 0.0,
    -1.0, -1.0, 0.0,
    1.0, -1.0, 0.0,
    1.0, 1.0, 0.0
}

Ground::Ground() {
    // Create Shader Program
    // TODO

    // Get Uniform Locations
    // TODO

    // Gen vertex buffers
    // TODO
}

Ground::~Ground() {
    // Undo everything
    // TODO
}

void Ground::render(vec3 player, mat4 PV) {
    // Enable shader
    // TODO

    // Shader specific setup
    // TODO

    // Do all mandatory draw operations
    drawCall(player, );

    // Teardown
    // TODO
}

void Ground::drawCall(vec3 player, GLint M_location) {
    // First we create a model transform to scale the ground and move it under the player
    mat4 M = mat4();
    M = scale(M, vec3(vec2(vec3(groundExtent)), 0.0));
    M = translate(M, vec3(vec2(player), 0.0));

    // Upload to uniform
    // TODO

    // Draw quad
    // TODO
}
