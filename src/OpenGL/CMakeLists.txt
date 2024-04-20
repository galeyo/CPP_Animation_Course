project(CPP_Animation_Course_OpenGL)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add all Source Files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

# Add all Header Files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME}
	PUBLIC ${STB_ROOT_DIR}/include
	PUBLIC ${Vulkan_INCLUDE_DIRS}
	PUBLIC ${GLFW_ROOT_DIR}/include
	PUBLIC ${GLAD_ROOT_DIR}/include
)

target_link_directories(${PROJECT_NAME} 
	PRIVATE ${GLFW_ROOT_DIR}/src
	PRIVATE ${GLAD_ROOT_DIR}/src
)

target_link_libraries(${PROJECT_NAME} glfw opengl32 glad)

add_custom_command(TARGET ${PROJECT_NAME}
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/Shaders
) 
add_custom_command(TARGET ${PROJECT_NAME}
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_CURRENT_SOURCE_DIR}/Textures $<TARGET_FILE_DIR:${PROJECT_NAME}>/Textures
) 