#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define RESOLUTION_Y 1000
#define RESOLUTION_X 1000
#define PI 3.14159265358979323846

const int row = 3;
const int col = 2;
const int rowWidth = col + 1;
int indexCount = col*(row - 1)*6;

void framebuffer(GLFWwindow* window, int width, int height);
float *Sphere();
unsigned int *Sphere_Indices();
void convertFileToString(char* strBuffer, FILE* shaderFile);

//in indicing for a Sphere we take our 3x3 points and connect them into 4 squares
//we divid that into 8 triangles, there are 2 ways we can indice our points clockwise
//or counter-clockwise and to not get confused it is best to choose 1 way
//for all our triangles

int main()
{
    //reading shader files
    FILE *vertexFile = fopen("VertexShader.vs", "r");
    FILE *fragmentFile = fopen("FragmentShader.fs", "r");
    //creating sizes to store my shader files onto string
    char *vertexSize = malloc(sizeof(char) * 2000);
    char *fragmentSize = malloc(sizeof(char) * 2000);
    //read file and convert to a string
    convertFileToString(vertexSize, vertexFile);
    convertFileToString(fragmentSize, fragmentFile);
    const char* vertexString = vertexSize;
    const char* fragmentString = fragmentSize;
    fclose(vertexFile);
    fclose(fragmentFile);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(RESOLUTION_X, RESOLUTION_Y, "SphereScene", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((void*)glfwGetProcAddress);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glfwSetFramebufferSizeCallback(window, framebuffer);

    //compiling vertex shader
    //Creating a variable id to use later as our key to access our shader
    unsigned int vertexID = 0;
    //creating a shader object
    vertexID = glCreateShader(GL_VERTEX_SHADER);
    //Loading the shader string into the vertexID which is our key
    glShaderSource(vertexID, 1, &vertexString, NULL);
    //compile the shader so it can be used later
    glCompileShader(vertexID);
    //compiling fragment shader
    unsigned int fragmentID = 0;
    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentID, 1, &fragmentString, NULL);
    glCompileShader(fragmentID);
    //linking both shaders
    unsigned int shaderLink = 0;
    shaderLink = glCreateProgram();
    glAttachShader(shaderLink, vertexID);
    glAttachShader(shaderLink, fragmentID);
    glLinkProgram(shaderLink);

    free(vertexSize);
    free(fragmentSize);
    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

    //sphere creating
    float *sphere = Sphere();
    unsigned int *sphereIndices = Sphere_Indices();
    //VBO and VAO
    unsigned VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float) * row * rowWidth * 3, sphere,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexCount, sphereIndices, GL_STATIC_DRAW);

    free(sphere);
    free(sphereIndices);

    int colorLoc = glGetUniformLocation(shaderLink, "uColor");

    glPointSize(10.0f);
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.3f, 0.1f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //use shader
        glUseProgram(shaderLink);

        //draw sphere
        glBindVertexArray(VAO);
        glUniform3f(colorLoc, 0.0f, 0.0f, 0.0f);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

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

//10-27 notes:
//A sphere is a stack of plates. Each plate is a circle of col points.
//Going down, the plates change size and height.
//θ: 0° → 180°, radius = sin θ, y = cos θ. sin = 0 at both ends seals the top and bottom.
//φ: 0° → 360°, x = sin θ cos φ, z = sin θ sin φ.

float *Sphere()
{
    int point;
    float theta;
    float phi;

    float x;
    float y;
    float z;

    int FloatPerVer = 3;
    float *sphere = malloc(sizeof(float) * row * rowWidth * FloatPerVer);

    for(int i = 0; i < row; i++)
    {
        theta = i * PI / (float)(row - 1);
        for(int j = 0; j < rowWidth; j++)
        {
            point = i * rowWidth + j;
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

//0 = a        1 = a + 1
//3 = a + col  4 = a + col + 1

//for col
//0 = a, 1 = a + 1 , 3 = a + col,
//3 = a + col, 1 = a + 1, 4 = a + col + 1
//these are our formulas to create indices
//2 per row with the connecting the dots to make a sphere we have to repeat so it will be 3

//for rowWidth;
//if a = 0, in a
//0 1
//4 5
//1 = a+1, 4 = a+rowWidth, 5 = a+rowWidth+1
unsigned int *Sphere_Indices()
{
    int a;
    unsigned int *sphereIndices = malloc(sizeof(unsigned int) * indexCount);
    int counter = 0;

    for(int i = 0; i < row - 1; i++)
    {
        for (int j = 0; j < col; j++)

        {
            a = i * rowWidth + j;
            sphereIndices[counter] = a;
            counter++;
            sphereIndices[counter] = a + 1;
            counter++;
            sphereIndices[counter] = a + rowWidth;
            counter++;
            sphereIndices[counter] = a + 1;
            counter++;
            sphereIndices[counter] = a + rowWidth + 1;
            counter++;
            sphereIndices[counter] = a + rowWidth;
            counter++;
        }
    }

    return sphereIndices;
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
