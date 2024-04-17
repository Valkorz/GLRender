#include <glew.h>
#include <iostream>
#include <GL/gl.h>
#include <glfw3.h>

//Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

int main(){

    std::cout << "AAAAAAAAAAAAAAAAAAA" << std::endl;

    // Initialize GLFW: starts library functions
    if( glfwInit() == GLFW_FALSE ){
        std::cout << "GLFW initialization failed!" << std::endl;
        glfwTerminate();
        return 1;
    }

    // Setup GLFW window properties
    // OpenGL version

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //Core profile (No backwards compatibility)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //Create window: creates window as a pointer, with some information.
    GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "TestWindow", NULL, NULL);
    if(!mainWindow){
        std::cout << "GLFW window creation failed!" << std::endl;
        glfwTerminate();
        return 1;
    }

    //Get Buffer size information: the data block dimensions where data will be held in the GPU
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    //Set context for GLEW to use: select target window for operations (newly created)
    glfwMakeContextCurrent(mainWindow);

    //Allow modern extension features
    glewExperimental = GL_TRUE;

    GLenum init = glewInit();
    if(init != GLEW_OK){
        std::cout << "Glew initialization failed!" << std::endl;
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    //Setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);

    //Loop until window closed
    while(!glfwWindowShouldClose(mainWindow)){
        //Get + handle user input events
        glfwPollEvents();

        //Clear window
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); //Clear all the colors to the above

        glfwSwapBuffers(mainWindow);
    }

    int t;
    std::cin >> t;
    return 0;
}