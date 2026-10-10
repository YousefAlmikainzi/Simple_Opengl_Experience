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

//drew 9 points in an 3x3 formation
//made from them 3 triangles since that is what makes a slice horizontally across a 3x3 points
//using different sizes for each slice to showcase how a sphere closes and the top and bottom and widest in the middle, sin(0) means bottom or top of sphere
//finally understanding opp in right triangle is what gets us our radius for horizontal
// slice radius = sin(θ), height = cos(θ), θ: 0 → 180
// φ is the angle adj to x-axis
// and knowing that we can get our formulas
// radius = sin(theta)
//x = radius * cos (φ)
//y = cos(theta)
//z = radius * sin(φ)
