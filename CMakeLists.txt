cmake_minimum_required(VERSION 2.6)
project(YseEngine)

#Version Number
set (YseEngine_VERSION_MAJOR 1)
set (YseEngine_VERSION_MINOR 0)

# Header file config to pass to source
configure_file(	
	"${PROJECT_SOURCE_DIR}/YseEngineConfig.h.in"
	"${PROJECT_BINARY_DIR}/YseEngineConfig.h"
	)

# Add binary tree to search path for includes
# to find YseEngineConfig.h
include_directories("{$PROJECT_BINARY_DIR}")

# Add the executable
add_executable(YseEngine YseEngine.cxx)

