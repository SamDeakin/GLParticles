#pragma once

#include <GL/gl3w.h>
#include <string>
#include <map>

#include "exception.hpp"

#if(DEBUG)
    #define CHECK_GL_ERRORS checkGLErrors(__FILE__, __LINE__)
    #define CHECK_FRAMEBUFFER_COMPLETENESS checkFramebufferCompleteness()
#else
    #define CHECK_GL_ERRORS
    #define CHECK_FRAMEBUFFER_COMPLETENESS
#endif

void checkGLErrors(const std::string & currentFileName, int currentLineNumber);

void checkFramebufferCompleteness();

// Just a stub
class GLException : public Exception {
public:
    GLException(const std::string &message) : Exception(message) {}
};
