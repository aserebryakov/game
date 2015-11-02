cmake_minimum_required (VERSION 3.0)
project (game)

set(GCC_COVERAGE_COMPILE_FLAGS "-std=c++0x")
set(GCC_COVERAGE_LINK_FLAGS    "")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

file (GLOB GameSources "src/*.cc")

find_package(SDL2 REQUIRED)
if (SDL_FOUND)
    include_directories(${SDL_INCLUDE_DIR})
    link_libraries(${SDL_LIBRARY})
endif (SDL_FOUND)

find_package(SDL2_ttf REQUIRED)
if (SDL2_TTF_FOUND)
    include_directories(${SDL_TTF_INCLUDE_DIRS})
    link_libraries(${SDL_TTF_LIBRARIES})
endif (SDL2_TTF_FOUND)

find_package(SDL2_image REQUIRED)
if (SDL2_IMAGE_FOUND)
    include_directories(${SDL_IMAGE_INCLUDE_DIRS})
    link_libraries(${SDL_IMAGE_LIBRARIES})
endif (SDL2_IMAGE_FOUND)

include_directories("include")
add_executable (game ${GameSources})
