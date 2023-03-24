cmake_minimum_required(VERSION 3.0)

######################################
# User build configuration
######################################


# =========================
# Global settings
# =========================

set(CMAKE_CXX_STANDARD 20)

######################################
# Setup target
######################################

# Files
file(
	GLOB_RECURSE
	SOURCES
	CONFIGURE_DEPENDS 
	"./src/*.cpp"
)
file(
	GLOB
	HEADERS
	CONFIGURE_DEPENDS 
	"./include/*"
)

add_executable(simulator ${SOURCES} ${HEADERS})
set_target_properties(simulator PROPERTIES OUTPUT_NAME "board")
target_include_directories(simulator PRIVATE ./include)