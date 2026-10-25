#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "shader.hpp"
#include "camera.hpp"
#include "stb_image.h"

// Global variables
LearnOpenGLCamera::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
// Cursor location initialsed at the center of the screen
float lastX = 400, lastY = 300;
bool  firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

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

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX      = xpos;
        lastY      = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera.ProcessMouseMovement(xoffset, yoffset, true);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Resize the glViewport after window resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    LearnOpenGLShader::Shader ourShader("shaders/vertex.glsl",
                                        "shaders/fragment.glsl");
    // Light Source cube
    LearnOpenGLShader::Shader lightCubeShader("shaders/light_vertex.glsl",
                                              "shaders/light_fragment.glsl");
    // Copied from learn opengl

    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f,  //
        0.5f,  -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f,  //
        0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f,  //
        0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f,  //
        -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f,  //
        -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f,  //

        -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  //
        0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  //
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  //
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  //
        -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  //
        -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  //

        -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  //
        -0.5f, 0.5f,  -0.5f, -1.0f, 0.0f,  0.0f,  //
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  //
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  //
        -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f,  //
        -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  //

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  //
        0.5f,  0.5f,  -0.5f, 1.0f,  0.0f,  0.0f,  //
        0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  //
        0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  //
        0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  //
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  //

        -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  //
        0.5f,  -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  //
        0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  //
        0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  //
        -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  //
        -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  //

        -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  //
        0.5f,  0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  //
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  //
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  //
        -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  //
        -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f   //
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

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Light VAO
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime          = currentFrame - lastFrame;
        lastFrame          = currentFrame;

        processInput(window);

        glfwSetCursorPosCallback(window, mouse_callback);

        glfwSetScrollCallback(window, scroll_callback);

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Coordinate system
        glm::mat4 model;

        // Camera logic
        glm::mat4 view;

        view = camera.GetViewMatrix();

        // This needs to be before the glUniform for them to work
        // void use() { glUseProgram(ID); }
        // ID is the glCreateProgram()
        ourShader.use();

        // Lighting
        int lightColourLoc = glGetUniformLocation(ourShader.ID, "lightColour");
        glUniform3f(lightColourLoc, 1.0f, 1.0f, 1.0f);

        int objectColourLoc =
            glGetUniformLocation(ourShader.ID, "objectColour");
        glUniform3f(objectColourLoc, 1.0f, 0.5f, 0.31f);

        int lightPosLoc = glGetUniformLocation(ourShader.ID, "lightPos");
        glUniform3fv(lightPosLoc, 1, &lightPos[0]);

        int viewPosLoc = glGetUniformLocation(ourShader.ID, "viewPos");
        glUniform3fv(viewPosLoc, 1, &camera.Position[0]);

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(camera.Zoom),
                                      800.0f / 600.0f, 0.1f, 100.0f);

        int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
                           glm::value_ptr(projection));

        model = glm::mat4(1.0f);
        glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "model"), 1,
                           GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Light shader
        lightCubeShader.use();

        int light_projectionLoc =
            glGetUniformLocation(lightCubeShader.ID, "projection");
        glUniformMatrix4fv(light_projectionLoc, 1, GL_FALSE,
                           glm::value_ptr(projection));

        int light_viewLoc = glGetUniformLocation(lightCubeShader.ID, "view");
        glUniformMatrix4fv(light_viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        glUniformMatrix4fv(glGetUniformLocation(lightCubeShader.ID, "model"), 1,
                           GL_FALSE, glm::value_ptr(model));

        // render container
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &lightVAO);

    // Get maximum number of vertex
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes
              << std::endl;

    // Terminate window
    glfwTerminate();

    return 0;
}
