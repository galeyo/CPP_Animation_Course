project(CPP_Animation_Course_Vulkan)
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
	PUBLIC ${Vulkan_INCLUDE_DIRS}
	PUBLIC ${GLFW_ROOT_DIR}/include
)
target_link_directories(${PROJECT_NAME} 
	PRIVATE ${GLFW_ROOT_DIR}/src
)


target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan glfw)