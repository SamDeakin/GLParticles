#pragma once
/*
 * An abstraction of an OpenGL shader
 *
 * A nod to my CS488 profs for this file.
 */
#include <GL/gl3w.h>
#include <string>


class GLShaderProgram {
public:
    GLShaderProgram();
    ~GLShaderProgram();

    /*
     * We create the actual OpenGL object here
     * This is it's own public function not called by ctor
     * so that we can lazily initialize the OpenGL objects
     */
    void generateProgramObject();

    void attachVertexShader(const char * filePath);
    void attachFragmentShader(const char * filePath);
    void attachGeometryShader(const char * filePath);

    void link();
    void enable() const;
    void disable() const;
    void recompileShaders();

    GLuint getProgramObject() const;
    GLint getUniformLocation(const char * uniformName) const;
    GLint getAttribLocation(const char * attributeName) const;
private:
    struct GLShaderObject {
        GLuint shaderObject;
        std::string filePath;

        GLShaderObject();
    };

    // We only support a single shader of the same type at the moment
    GLShaderObject vertexShader;
    GLShaderObject fragmentShader;
    GLShaderObject geometryShader;

    GLuint programObject;

    void extractSourceCode(std::string & shaderSource, const std::string & filePath);
    void extractSourceCodeAndCompile(const GLShaderObject &shader);

    GLuint createShader(GLenum shaderType);
    void compileShader(GLuint shaderObject, const std::string & shader);

    void checkCompilationStatus(GLuint shaderObject);
    void checkLinkStatus();

    void deleteShaders();
};
