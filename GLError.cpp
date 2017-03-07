#include <string>
#include <sstream>

#include "GLError.hpp"

using namespace std;

// Translate GL error codes to a string
// The string is literally just the error code name
std::map<GLenum, std::string> errorMap = {
    {GL_NO_ERROR, "GL_NO_ERROR"},
    {GL_INVALID_ENUM, "GL_INVALID_ENUM"},
    {GL_INVALID_VALUE, "GL_INVALID_VALUE"},
    {GL_INVALID_OPERATION, "GL_INVALID_OPERATION"},
    {GL_OUT_OF_MEMORY, "GL_OUT_OF_MEMORY"},
    {GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT, "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT"},
    {GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT, "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT"},
    {GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER, "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER"},
    {GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER, "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER"},
    {GL_FRAMEBUFFER_UNSUPPORTED, "GL_FRAMEBUFFER_UNSUPPORTED"},
    {GL_FRAMEBUFFER_UNDEFINED, "GL_FRAMEBUFFER_UNDEFINED"},
};

void checkGLErrors(const string &currentFileName, int currentLine) {
    GLenum errorCode;
    bool errorFound = false;
    stringstream errorMessage;

    // Write all errors to errorMessage stringstream until error list is exhausted.
    do {
        errorCode = glGetError();

        if (errorCode != GL_NO_ERROR) {
            errorMessage << "[GL Error Code " << errorCode <<  ": " << errorMap[errorCode] << " "
            << " at " << currentFileName << ":" << currentLine << "]" << endl;

            errorFound = true;
        }
        errorCode = glGetError();
    } while (errorCode != GL_NO_ERROR);

    if (errorFound) {
        throw GLException(errorMessage.str());
    }
}

void checkFramebufferCompleteness() {
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        stringstream error;
        error << "Framebuffer incomplete: ";
        error << errorMap[status];
        throw GLException(error.str());
    }
}
