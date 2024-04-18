#include <glew.h>
#include <iostream>
#include <GL/gl.h>
#include <glfw3.h>
#include <string.h>

/*
    This is the script for rendering an OpenGL program, which consists in initializing a window with GLFW and GLEW,
    creating a new shader and rendering a shape. 
*/


//Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

//Create Vertex Array Object for storing all vertices. Vertex Buffer Object for storing vertex data. Shader for additional data.
GLuint VAO, VBO, shader;

/*
    ||| START OF GLSL |||
*/

//Set position in vertex shader
static const char* vShader = "                                  \n\
#version 330                                                    \n\
                                                                \n\
layout(location = 0) in vec3 pos;                               \n\
                                                                \n\
void main()                                                     \n\
{                                                               \n\           
    gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);   \n\
}";

//Set color in fragment shader
static const char* fShader = "                                  \n\
#version 330                                                    \n\
                                                                \n\
out vec4 color;                                                 \n\
                                                                \n\
void main()                                                     \n\
{                                                               \n\     
    color = vec4(0.0, 0.0, 0.0, 1.0);                           \n\
}";

/*
    ||| END OF GLSL |||
*/

void createTriangle(){

    //Set 3 points for the triangle (x,y,z)
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    //generate a VAO and VBO ID and pass it to their variables (as a pointers) and bind them to VAO and VBO.
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); 

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Pass the amount of data. In this case the amount of vertices.
    //GL_STATIC_DRAW: point values won't be changed;
    //GL_DYNAMIC_DRAW: point values may change;

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //Attributes for the primitive, such as index, size, variable type...
    glEnableVertexAttribArray(0); //Connects array attributes to the pointer (with index 0)

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); //Bind array and data to index 0
}

//Add shader to program
void addShader(GLuint program, const char* shaderCode, GLenum shaderType){

    //Create an empty shader with the specified type
    GLuint progShader = glCreateShader(shaderType);

    //code string pointer
    const GLchar* progCode[1];
    progCode[0] = shaderCode;

    //code length
    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    //Count means the number of chunks
    glShaderSource(progShader, 1, progCode, codeLength);
    glCompileShader(progShader);

    GLint result = 0;
    GLchar log[1024] = { 0 };

    glGetShaderiv(progShader, GL_COMPILE_STATUS, &result); //Get result from linking shader info
    if(!result){
        glGetShaderInfoLog(progShader, sizeof(log), NULL, log);
        std::cout << "Error compiling shader " << shaderType << ": " << log << std::endl;
        return;
    }

    glAttachShader(program, progShader);
}

//Compile shader and check if procedure failed.
void compileShaders(){
    shader = glCreateProgram();

    if(!shader){
        std::cout << "Error creating shader program! (Unhandled exception)" << std::endl;
        return;
    }

    addShader(shader, vShader, GL_VERTEX_SHADER);
    addShader(shader, fShader, GL_FRAGMENT_SHADER);

    //Function results
    GLint result = 0;
    GLchar log[1024] = { 0 };

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result); //Get result from linking shader info

    if(!result){
        glGetProgramInfoLog(shader, sizeof(log), NULL, log);
        std::cout << "Error linking program: " << log << std::endl;
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result); //Get validation status
     if(!result){
        glGetProgramInfoLog(shader, sizeof(log), NULL, log);
        std::cout << "Error validating program: " << log << std::endl;
        return;
    }
}

int main(){

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

    createTriangle();
    compileShaders();

    //Loop until window closed
    while(!glfwWindowShouldClose(mainWindow)){
        //Get + handle user input events
        glfwPollEvents();

        //Clear window
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); //Clear all the colors to the above

        //Activate shader program
        glUseProgram(shader);

            //Bind shader to target vertex
            glBindVertexArray(VAO);
            //Notify system to fill gaps to draw a triangle
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);

        glUseProgram(0);

        glfwSwapBuffers(mainWindow);
    }

    int t;
    std::cin >> t;
    return 0;
}