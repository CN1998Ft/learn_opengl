#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shader.hpp"

/**
 * @brief callback functions to resize the window
 *
 * This function take input like window, width and height to resize the opengl
 * viewport when called.
 *
 * @param[in] window
 * @param[in]  width
 * @param[in]  height
 * @return     void
 */
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/**
 * @brief process input key
 *
 * This function monitors the key pressed when the GLFW window is focused.
 *
 * @param[in] window
 * @return     void
 */
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main()
{
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow *window;

    window =
        glfwCreateWindow(800, 600, "LearnOpengl_FloatingWindow", NULL, NULL);

    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialise the glad for loading OpenGL functions.
    int version = gladLoadGL(glfwGetProcAddress);

    if (!version)
    {
        std::cout << "Failed to initialise GLAD" << std::endl;
        return -1;
    }

    printf("OpenGL %d.%d\n", GLAD_VERSION_MAJOR(version),
           GLAD_VERSION_MINOR(version));

    glViewport(0, 0, 800, 600);
    // Resize the glViewport after window resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    LearnOpenGLShader::Shader ourShader("shaders/vertex.glsl",
                                        "shaders/fragment.glsl");
    // Answer_2: can also just change the position y values
    float vertices[] = {
        // positions        // colors
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // top
    };

    // Vertex Buffer Object
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Answer_1
    float offset = 0.5f;
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // glClearColor(0.8f, 0.3f, 0.8f, 1.0f);
        // glClear will fill the buffer with the color defined by glClearColor.
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();
        // Answer_1
        ourShader.setFloat("xOffset", offset);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    // Get maximum number of vertex
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes
              << std::endl;

    // Terminate window
    glfwTerminate();
    return 0;
}
