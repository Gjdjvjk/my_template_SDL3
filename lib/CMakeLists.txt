add_library(game_lib STATIC)

target_sources(game_lib PRIVATE
    src/Paths.cpp
    src/Game.cpp
    src/Cube.cpp
)

target_include_directories(game_lib PUBLIC include)

target_link_libraries(game_lib PUBLIC
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
)

target_compile_definitions(game_lib PRIVATE
    $<$<NOT:$<BOOL:${ASSETS_DIR}>>:ASSETS_DIR="assets">
    $<$<BOOL:${ASSETS_DIR}>:ASSETS_DIR="${ASSETS_DIR}">
)
