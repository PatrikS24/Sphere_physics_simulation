cmake_minimum_required(VERSION 3.22)
project(C___program)

set(CMAKE_CXX_STANDARD 20)

# Your own include directory
include_directories(include)

# === ImGui library ===
add_library(imgui
        libs/imgui/imgui.cpp
        libs/imgui/imgui_draw.cpp
        libs/imgui/imgui_widgets.cpp
        libs/imgui/imgui_tables.cpp
        libs/imgui/backends/imgui_impl_opengl3.cpp
)

# Include paths for ImGui
target_include_directories(imgui PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends
)

# === Your executable ===
add_executable(C___program
        main.cpp
        include/RigidBody.h
        include/TransformStructs.h
        include/Sphere.h
        include/Vector.h
        include/World.h
        src/Sphere.cpp
        src/World.cpp
)

# Tell your executable to link to ImGui
target_link_libraries(C___program PRIVATE imgui)

# Include ImGui headers for your executable
target_include_directories(C___program PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends
)

# === OpenGL & FreeGLUT ===
find_package(OpenGL REQUIRED)

set(FREEGLUT_INCLUDE_DIR "C:/msys64/mingw64/include")
set(FREEGLUT_LIB_DIR "C:/msys64/mingw64/lib")

include_directories(${FREEGLUT_INCLUDE_DIR})
link_directories(${FREEGLUT_LIB_DIR})

target_link_libraries(C___program PRIVATE
        imgui           # link ImGui
        ${OPENGL_LIBRARIES}
        freeglut
        opengl32
)
