#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fm/fmath.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#define SCREENWIDTH 1280
#define SCREENHEIGHT 720

void DrawCube(GLuint shaderProgram, GLuint cubeVAO, fm::vec3 location, fm::quat rotation, fm::vec3 size, fm::vec4 color);

GLuint CompileShader(GLenum type, const char* source);
GLuint CreateShaderProgram(const char* vertexSource, const char* fragmentSource);
GLuint CreateCubeVAO();

extern const char* vertexShaderSource;
extern const char* fragmentShaderSource;