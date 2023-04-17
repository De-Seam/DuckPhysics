#include <Examples/ExampleRenderer.h>

int main() 
{
    // Initialize GLFW
    if (!glfwInit()) 
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a window and OpenGL context
    GLFWwindow* window = glfwCreateWindow(SCREENWIDTH, SCREENHEIGHT, "OpenGL Cube", nullptr, nullptr);
    if (!window) 
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) 
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;

        glfwTerminate();
        return -1;
    }

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);


    // Create the shader program
    GLuint shaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);

    // Create the cube VAO
    GLuint cubeVAO = CreateCubeVAO();

    // Set up the camera matrices
    glm::mat4 projection = glm::perspective(fm::to_radians(70.f), static_cast<float>(SCREENWIDTH) / static_cast<float>(SCREENHEIGHT), 0.1f, 1000.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, -5.f, 0.f),
                                  glm::vec3(0.0f, 0.0f, 0.0f),
                                  glm::vec3(0.0f, 0.f, 1.0f));

    // Set the projection and view matrices in the shader
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);

    // Main loop
    while (!glfwWindowShouldClose(window)) 
    {
        // Clear the screen
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw the cube
        DrawCube(shaderProgram, cubeVAO,
                 fm::vec3(0.0f, 0.0f, 0.0f),
                 fm::quat(fm::vec3(0.0f, fm::to_radians(45.0f), 0.0f)),
                 fm::vec3(1.0f, 1.0f, 1.0f),
                 fm::vec4(1.f, 0.5f, 1.0f, 1.0f));

        DrawCube(shaderProgram, cubeVAO,
                 fm::vec3(1.f, 1.f, 1.f),
                 fm::quat(fm::vec3(0.0f, fm::to_radians(45.0f), 0.0f)),
                 fm::vec3(1.0f, 1.0f, 1.0f),
                 fm::vec4(0.f, 0.5f, 1.0f, 1.0f));

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glDeleteVertexArrays(1, &cubeVAO);
    //glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();

    return 0;
}