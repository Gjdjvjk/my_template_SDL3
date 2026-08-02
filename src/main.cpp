#include <game/Game.h>
#include <game/Paths.h>

#include <cstdio>

Game* g_game = nullptr;

int main(int argc, char* argv[])
{
    g_game = new Game("SDL3 Template", 25, 25, 1280, 720, 0);

    std::printf("Assets path: %s\n", GetAssetsPath().c_str());

    g_game->run();

    return 0;
}
