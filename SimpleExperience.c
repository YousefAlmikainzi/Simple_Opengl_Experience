#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define RESOLUTION_Y 800
#define RESOLUTION_X 1000
#define PI 3.14159265358979323846

void framebuffer(GLFWwindow* window, int width, int height);
float *Sphere();
void convertFileToString(char* strBuffer, FILE* shaderFile);

int main()
{
    //reading shader files
    FILE *vertexFile = fopen("VertexShader.vs", "r");
    FILE *fragmentFile = fopen("FragmentShader.fs", "r");
    //creating sizes to store my shader files onto string
    char *vertexSize = malloc(sizeof(char) * 1000);
    char *fragmentSize = malloc(sizeof(char) * 1000);


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
//θ = i × π ÷ (rows − 1)
//φ = j × 2π ÷ (col)

float *Sphere()
{
    int row = 3;
    int col = 3;

    int point;
    float theta;
    float phi;

    float x;
    float y;
    float z;

    int FloatPerVer = 3;
    float *sphere = malloc(sizeof(float) * row * col * FloatPerVer);

    for(int i = 0; i < row; i++)
    {
        theta = i * PI / (float)(row - 1);
        for(int j = 0; j < col; j++)
        {
            point = i * col + j;
            phi = j * 2*PI / col;
            x = sin(theta) * cos (phi);
            y = cos(theta);
            z = sin(theta) * sin(phi);
            sphere[point * FloatPerVer + 0] = x;
            sphere[point * FloatPerVer + 1] = y;
            sphere[point * FloatPerVer + 2] = z;
        }
    }
    return sphere;
}

void convertFileToString(char* strBuffer, FILE* shaderFile)
{
    //doing this make whenever the file is interacted with it would be at the end of the file
    fseek(shaderFile, 0, SEEK_END);
    long fileSize = ftell(shaderFile);
    rewind(shaderFile);
    //convert the shaderFile into string so I can use it
    fread(strBuffer, 1, fileSize, shaderFile);
    strBuffer[fileSize] = '\0';
}
