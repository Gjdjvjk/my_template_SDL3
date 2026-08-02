#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "SDL3/SDL_video.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <game/Cube.h>

#define FPS 60
#define FRAME_TIME 1000/FPS

class Game {
public:
    Game();
    Game(const char* title, int xpos, int ypos, int width, int height, SDL_WindowFlags flags);
    Game(const char* title, int width, int height);
    ~Game();

    bool init(const char* title, int xpos, int ypos, int width, int height, SDL_WindowFlags flags);
    void run();
    bool is_running() const;
    
    SDL_Window*   window()   const;
    SDL_Renderer* renderer() const;
    
private:
    void handleEvent(const SDL_Event& event);
    void update(float deltaTime);
    void render();
    void clean();
    void shutdown();

    SDL_Window*   m_pWindow;
    SDL_Renderer* m_pRenderer;
    bool          m_bRunning;
    Cube          m_cube;
};


#endif
