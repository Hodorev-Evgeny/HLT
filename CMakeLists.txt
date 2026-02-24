cmake_minimum_required(VERSION 3.10)
project(HLT)

set(CMAKE_CXX_STANDARD 17)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)


add_subdirectory(dependencies/glfw-3.3.2)

add_executable(HLT
		main.cpp
		dependencies/glad/src/glad.c
)

target_include_directories(HLT PRIVATE
		dependencies/include
		dependencies/glad/include
		dependencies/glfw-3.3.2/include
		dependencies/glm
		dependencies/imgui-docking
		dependencies/raudio
		dependencies/stb_image
		dependencies/stb_truetype
)


target_link_libraries(HLT PRIVATE
		glfw
		opengl32
		-mconsole
)