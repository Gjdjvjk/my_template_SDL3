#include <game/Game.h>
#include <game/Paths.h>

#include <cstdio>

Game::Game() = default;

Game::~Game()
{
    clean();
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
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
    if (!m_bRunning)
        return;

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
            handleEvent(event);

        update(deltaTime);
        render();
    }
}

void Game::handleEvent(const SDL_Event& event)
{
    if (event.type == SDL_EVENT_QUIT)
        m_bRunning = false;
}

void Game::update(float /*deltaTime*/)
{
}

void Game::render()
{
    SDL_SetRenderDrawColor(m_pRenderer, 0x1a, 0x1a, 0x2e, 0xff);
    SDL_RenderClear(m_pRenderer);
    SDL_RenderPresent(m_pRenderer);
}

void Game::clean() { }

SDL_Window* Game::window() const { return m_pWindow; }
SDL_Renderer* Game::renderer() const { return m_pRenderer; }
