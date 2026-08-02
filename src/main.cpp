#include <game/Game.h>
#include <game/Paths.h>

#include <cstdio>

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    Game game;
    if (!game.init("SDL3 Template", 1280, 720, 1280, 720, 0))
    {
        std::fprintf(stderr, "Failed to initialize game.\n");
        return 1;
    }

    std::printf("Assets path: %s\n", GetAssetsPath().c_str());

    game.run();
    game.shutdown();

    return 0;
}
