// OpenGLCourseApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Wallace Obey 

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string.h>

// Window Dimensions
const GLint WIDTH = 800;
const GLint HEIGHT = 600; 

GLuint VAO, VBO, shader; 

// Vertex Shader 
static const char* vShader = "                                  \n\
#version 330                                                    \n\
                                                                \n\
layout (location = 0) in vec3 pos;                              \n\
                                                                \n\
void main()                                                     \n\
{                                                               \n\
    GL_POSITION = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);   \n\
}";

// Fragment Shader 
static const char* fShader = "                                  \n\
#version 330                                                    \n\
                                                                \n\
out vec4 colour;                                                \n\
                                                                \n\
void main()                                                     \n\
{                                                               \n\
    colour = vec4(1.0f, 0.0, 0.0, 1.0);                         \n\
}";

void CreateTriangle()
{
    // Create VAO and VBO - define how a triangle should be drawn - multiple VBOs to a VAO
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO); 
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0); 
}

void AddShaders(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
    GLuint theShader = glCreateShader(shaderType); // pass shader type

    const GLchar* theCode[1]; 
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode); 

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader); 

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glGetProgramiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
        printf("Error comiling the  %d shader: '%s' \n", shaderType, eLog);
        return;
    }

    glGetAttachedShaders()

    return; 
}

void CompileShaders()
{
    shader = glCreateProgram(); 

    if (!shader)
    {
        printf("Error creating shader program! \n");
        return; 
    }
    AddShaders(shader, vShader, GL_VERTEX_SHADER);
    AddShaders(shader, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0; 
    GLchar eLog[1024] = { 0 }; 

    glLinkProgram(shader); 
    glGetProgramiv(shader, GL_LINK_STATUS, &result); 
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error linking program: '%s' \n", eLog); 
        return;
    }

    glValidateProgram(shader); 
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error validating program: '%s' \n", eLog);
        return;
    }

}

int main()
{
    std::cout << "Hello World!" << std::endl;

    // Initialize GLFW 
    if (!glfwInit())
    {
        std::cout << " GLFW Initialization Failed :( " << std::endl; 
        glfwTerminate(); 
        return 1; 
    }

    // Setup GLFW window Perperties
    // OpenGL version 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Version 3.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Version 3.3
    // Don't use deprocated features | Core profile = No Backwards Compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
    // Allow forward Compatability
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 

    GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
    if (!mainWindow)
    {
        std::cout << "GLFW Window Creation Failed" << std::endl; 
        glfwTerminate();
        return 1; 
    }

    // Get Buffer size Information 
    int bufferWidth;
    int bufferHeight; 
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight); 

    // Set Context for GLEW to Use
    glfwMakeContextCurrent(mainWindow); // current window to draw to etc...

    // Allow modern extension features
    glewExperimental = GL_TRUE; 

    if (glewInit() != GLEW_OK)
    {
        std::cout << " GlEW Initialization Failed " << std::endl; 
        glfwDestroyWindow(mainWindow); 
        glfwTerminate();
        return 1; 
    }

    // Create Viewport
    glViewport(0, 0, bufferWidth, bufferHeight); 

    CreateTriangle();
    CompileShaders(); 

    // Loop until window closed 
    while (!glfwWindowShouldClose(mainWindow))
    {
        // Get + Handle user input events
        glfwPollEvents(); 

        // clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // clear entire screen and set color - RGB Value 0.0-1.0)
        glClear(GL_COLOR_BUFFER_BIT); 

        //actual drawing 
        glUseProgram(shader);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glUseProgram(0); 

        glfwSwapBuffers(mainWindow);
    }

     
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
