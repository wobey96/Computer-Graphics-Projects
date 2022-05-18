// OpenGLCourseApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Window Dimensions
const GLint WIDTH = 800;
const GLint HEIGHT = 600; 



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

    // Setup Viewport Size 
    glViewport(0, 0, bufferWidth, bufferHeight); 

    // Loop until window closed 
    while (!glfwWindowShouldClose(mainWindow))
    {
        // Get + Handle user input events
        glfwPollEvents(); 

        // clear window
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // clear entire screen and set color - RGB Value 0.0-1.0)
        glClear(GL_COLOR_BUFFER_BIT); 

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
