#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define RESOLUTION_Y 800
#define RESOLUTION_X 1000

void framebuffer(GLFWwindow* window, int width, int height);
void readEntireFile(char* strBuffer, FILE* shaderFile);

int main()
{
    glfwInit();
    GLFWwindow *window = glfwCreateWindow(RESOLUTION_X, RESOLUTION_Y, "OpenGlScene", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((void*)glfwGetProcAddress);
    glEnable(GL_DEPTH_TEST);
    glfwSetFramebufferSizeCallback(window, framebuffer);

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.3f, 0.1f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}

void framebuffer(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width, height);
}

