cmake_minimum_required(VERSION 3.24)
project(SDL_template LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.26   
)

FetchContent_Declare(SDL3_image
    GIT_REPOSITORY  https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-3.2.0
)

FetchContent_Declare(SDL3_ttf
    GIT_REPOSITORY  https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-3.2.0
)

# FetchContent_Declare(SDL3_mixer
#     GIT_REPOSITORY  https://github.com/libsdl-org/SDL_mixer.git
#     GIT_TAG main
# )

set(SDL_PIPEWIRE OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SDL3)

FetchContent_GetProperties(SDL3)
list(APPEND CMAKE_PREFIX_PATH "${sdl3_BINARY_DIR}")

FetchContent_MakeAvailable(
    SDL3_image
    SDL3_ttf
    # SDL3_mixer
    )

add_subdirectory(lib)
add_subdirectory(src)
