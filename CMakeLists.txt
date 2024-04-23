cmake_minimum_required(VERSION 3.10)
project(opengl)

set(SOURCES main.cpp display.cpp display.h
        shader.cpp
        shader.h
)
add_executable(opengl ${SOURCES})


set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGLU.so.1.3.1
        /usr/lib/x86_64-linux-gnu/libGL.so.1.7.0
)
set(SDL2_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.2600.5)
set(GLEW_LIBRARY /usr/lib/x86_64-linux-gnu/libGLEW.so.2.2.0)


message(STATUS "OpenGL libraries: ${OPENGL_LIBRARIES}")
message(STATUS "SDL2 library: ${SDL2_LIBRARY}")
message(STATUS "GLEW library: ${GLEW_LIBRARY}")


include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})

target_link_libraries(opengl ${SDL2_LIBRARY} ${GLEW_LIBRARY} ${OPENGL_LIBRARIES})

