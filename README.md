This project was created as part of my computer graphics rendering with OpenGL course. 
All rights reserved to the developers of OpenGL, GLEW and GLFW.

Steps to get this project working in *visual studio code*:

-Make sure you've got your graphics drivers updated;
-Download the libraries GLFW and GLEW for window rendering

-Get the libraries inside the project folder after unzipping

-Specify include folders in "c_cpp_properties.json"

-(Optional)Create launch.json for external console output

-Add g++ compiler path if visual studio can't find the environment variable

-Add include folders (-I) in the Args of tasks.json

-Add libraries (-L) in the Args of tasks.json

-Reference libraries used (-l) in the Args of tasks.json (glew32, glfw3dll, opengl32)

-Add includes into main.cpp

-(Optional)Add dlls in the same directory as the executable if static linking doesn't work

-(Optional)Add libraries as environment variables;

NOTE: for this project I used the 32-bit versions of the libraries.
