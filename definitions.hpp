/*
 * Just random definitions that we want to be consistent between files
 */
#include <glm/glm.hpp>

const double PI = 3.14159265359;

const double defaultVelocity = 1;
const double shiftMultiplyer = 2;

const double lookSensitivity = 0.001;

// Anyone that needs an up vector should use this value
const glm::vec3 canonicalUpVector = glm::vec3(0.0, 0.0, 1.0);
