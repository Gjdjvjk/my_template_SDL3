#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_video.h"
#include <game/Game.h>
#include <game/Paths.h>

#include <cstdio>

Game::Game() = default;

Game::Game(const char *title, int xpos, int ypos, int width, int height, SDL_WindowFlags flags) {
    if (!init( title, xpos, ypos, width, height, flags))
    {
        std::fprintf(stderr, "Failed to create: [Game] instance.\n");
    }
}

Game::Game(const char *title, int width, int height) {
    if (!init( title, 0, 0, width, height, 0))
    {
        std::fprintf(stderr, "Failed to create: [Game] instance.\n");
    }
}

Game::~Game()
{
    clean();
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, SDL_WindowFlags flags)
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        std::fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return false;
    }

    m_pWindow = SDL_CreateWindow(title, width, height, flags);
    if (!m_pWindow)
    {
        std::fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    SDL_SetWindowPosition(m_pWindow, xpos, ypos);

    m_pRenderer = SDL_CreateRenderer(m_pWindow, nullptr);
    if (!m_pRenderer)
    {
        std::fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(m_pWindow);
        SDL_Quit();
        return false;
    }

    if (!TTF_Init())
        std::fprintf(stderr, "TTF_Init warning: %s\n", SDL_GetError());

    m_bRunning = true;
    return true;
}

void Game::shutdown()
{
    m_bRunning = false;

    TTF_Quit();

    if (m_pRenderer) SDL_DestroyRenderer(m_pRenderer);
    if (m_pWindow)   SDL_DestroyWindow(m_pWindow);
    m_pRenderer = nullptr;
    m_pWindow   = nullptr;

    SDL_Quit();
}

void Game::run()
{
    Uint64 prevCounter = SDL_GetPerformanceCounter();

    while (m_bRunning)
    {
        const Uint64 currCounter = SDL_GetPerformanceCounter();
        const float deltaTime = static_cast<float>(
            static_cast<double>(currCounter - prevCounter)
            / static_cast<double>(SDL_GetPerformanceFrequency()));
        prevCounter = currCounter;

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            handleEvent(event);
        }

        update(deltaTime);

        render();
    }

    shutdown();
}

void Game::handleEvent(const SDL_Event& event)
{

    if (event.type == SDL_EVENT_QUIT) {
        m_bRunning = false;
    }

    if (event.key.down) {
        switch (event.key.key) {
            case SDLK_ESCAPE:
                m_bRunning = false;
                break;

            case SDLK_SPACE:
                if(m_cube.get_speed() == 0.0f)
                {
                    m_cube.set_speed(0.2f);
                }
                else {
                    m_cube.set_speed(0.0f);
                }
                break;

            case SDLK_LEFT:
                m_cube.set_speed(m_cube.get_speed() - 0.2f);
                break;

            case SDLK_RIGHT:
                m_cube.set_speed(m_cube.get_speed() + 0.2f);
                break;

            default:
                break;
        }
    }
}

void Game::update(float deltaTime)
{
    if (deltaTime < FRAME_TIME) {
        SDL_Delay(FRAME_TIME - deltaTime);
    }

    m_cube.update(deltaTime);
}

void Game::render()
{
    SDL_SetRenderDrawColor(m_pRenderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(m_pRenderer);

    // draw things here

    m_cube.render(m_pRenderer);

    SDL_RenderPresent(m_pRenderer);
}

void Game::clean() { }

SDL_Window* Game::window() const { return m_pWindow; }
SDL_Renderer* Game::renderer() const { return m_pRenderer; }
bool Game::is_running() const { return m_bRunning; }

