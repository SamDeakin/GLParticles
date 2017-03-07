#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

#include "GLShaderProgram.hpp"
#include "GLError.hpp"

using namespace std;
using namespace glm;

GLShaderProgram::GLShaderProgram() : programObject(0) {
    // Empty
}

GLShaderProgram::~GLShaderProgram() {
    deleteShaders();
}

void GLShaderProgram::generateProgramObject() {
    if(programObject == 0) {
        programObject = glCreateProgram();
    }
}

void GLShaderProgram::attachVertexShader (const char * filePath) {
    vertexShader.shaderObject = createShader(GL_VERTEX_SHADER);
    vertexShader.filePath = filePath;

    extractSourceCodeAndCompile(vertexShader);
}

void GLShaderProgram::attachFragmentShader (const char * filePath) {
    fragmentShader.shaderObject = createShader(GL_FRAGMENT_SHADER);
    fragmentShader.filePath = filePath;

    extractSourceCodeAndCompile(fragmentShader);
}

void GLShaderProgram::attachGeometryShader (const char * filePath) {
    geometryShader.shaderObject = createShader(GL_GEOMETRY_SHADER);
    geometryShader.filePath = filePath;

    extractSourceCodeAndCompile(geometryShader);
}

void GLShaderProgram::link() {
    if(vertexShader.shaderObject != 0) {
        glAttachShader(programObject, vertexShader.shaderObject);
    }

    if(fragmentShader.shaderObject != 0) {
        glAttachShader(programObject, fragmentShader.shaderObject);
    }

    if(geometryShader.shaderObject != 0) {
        glAttachShader(programObject, geometryShader.shaderObject);
    }

    glLinkProgram(programObject);
    checkLinkStatus();

    CHECK_GL_ERRORS;
}

void GLShaderProgram::enable() const {
    glUseProgram(programObject);
    CHECK_GL_ERRORS;
}

void GLShaderProgram::disable() const {
    glUseProgram((GLuint)NULL);
    CHECK_GL_ERRORS;
}

void GLShaderProgram::recompileShaders() {
    extractSourceCodeAndCompile(vertexShader);
    extractSourceCodeAndCompile(fragmentShader);
    extractSourceCodeAndCompile(geometryShader);
}

GLuint GLShaderProgram::getProgramObject() const {
    return programObject;
}

GLint GLShaderProgram::getUniformLocation (const char * uniformName) const {
    GLint result = glGetUniformLocation(programObject, (const GLchar *)uniformName);

    if (result == -1) {
        stringstream errorMessage;
        errorMessage << "Error obtaining uniform location: " << uniformName;
        throw GLException(errorMessage.str());
    }

    return result;
}

GLint GLShaderProgram::getAttribLocation (const char * attributeName) const {
    GLint result = glGetAttribLocation(programObject, (const GLchar *)attributeName);

    if (result == -1) {
        stringstream errorMessage;
        errorMessage << "Error obtaining attribute location: " << attributeName;
        throw GLException(errorMessage.str());
    }

    return result;
}

GLShaderProgram::GLShaderObject::GLShaderObject()
    : shaderObject(0),
      filePath() {
    // Empty
}

void GLShaderProgram::extractSourceCode (
        string & shaderSource,
        const string & filePath
) {
    ifstream file;

    file.open(filePath.c_str());
    if (!file) {
        stringstream strStream;
        strStream << "Error -- Failed to open file: " << filePath << endl;
        throw GLException(strStream.str());
    }

    stringstream strBuffer;
    string str;

    while(file.good()) {
        getline(file, str, '\r');
        strBuffer << str;
    }
    file.close();

    strBuffer << '\0';  // Append null terminator.

    shaderSource = strBuffer.str();
}

void GLShaderProgram::extractSourceCodeAndCompile (const GLShaderObject & shader) {
    string shaderSourceCode;
    extractSourceCode(shaderSourceCode, shader.filePath);

    compileShader(shader.shaderObject, shaderSourceCode);
}

GLuint GLShaderProgram::createShader (GLenum shaderType) {
    GLuint shaderId = glCreateShader(shaderType);
    CHECK_GL_ERRORS;

    return shaderId;
}

void GLShaderProgram::compileShader (
        GLuint shaderObject,
        const string & shaderSourceCode
) {
    const char * sourceCodeStr = shaderSourceCode.c_str();
    glShaderSource(shaderObject, 1, (const GLchar **)&sourceCodeStr, NULL);

    glCompileShader(shaderObject);
    checkCompilationStatus(shaderObject);

    CHECK_GL_ERRORS;
}

void GLShaderProgram::checkCompilationStatus (GLuint shaderObject) {
    GLint compileSuccess;

    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &compileSuccess);
    if (compileSuccess == GL_FALSE) {
        GLint errorMessageLength;
        // Get the length in chars of the compilation error message.
        glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &errorMessageLength);

        // Retrieve the compilation error message.
        GLchar errorMessage[errorMessageLength + 1]; // Add 1 for null terminator
        glGetShaderInfoLog(shaderObject, errorMessageLength, NULL, errorMessage);

        string message = "Error Compiling Shader: ";
        message += errorMessage;

        throw GLException(message);
    }
}

void GLShaderProgram::checkLinkStatus() {
    GLint linkSuccess;

    glGetProgramiv(programObject, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess == GL_FALSE) {
        GLint errorMessageLength;
        // Get the length in chars of the link error message.
        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &errorMessageLength);

        // Retrieve the link error message.
        GLchar errorMessage[errorMessageLength];
        glGetProgramInfoLog(programObject, errorMessageLength, NULL, errorMessage);

        stringstream strStream;
        strStream << "Error Linking Shaders: " << errorMessage << endl;

        throw GLException(strStream.str());
    }
}

void GLShaderProgram::deleteShaders() {
    glDeleteShader(vertexShader.shaderObject);
    glDeleteShader(fragmentShader.shaderObject);
    glDeleteProgram(programObject);
}
