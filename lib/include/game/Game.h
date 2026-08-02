#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

class Game {
public:
    Game();
    ~Game();

    bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
    void run();
    void clean();
    void shutdown();

    SDL_Window*   window() const;
    SDL_Renderer* renderer() const;

private:
    void handleEvent(const SDL_Event& event);
    void update(float deltaTime);
    void render();

    SDL_Window*   m_pWindow;
    SDL_Renderer* m_pRenderer;
    bool          m_bRunning;
};


#endif
