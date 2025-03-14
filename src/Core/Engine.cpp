#include "Engine.h"
#include "TextureManager.h"
#include "AppleThrower.h"
#include "Warrior.h"
#include "Input.h"
#include "SDL.h"
#include "Timer.h"

Engine* Engine::s_Instance = nullptr;

bool Engine::Init()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    m_Window = SDL_CreateWindow("Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(m_Window == nullptr) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    if (TTF_Init() == -1) {
        std::cout << "Lỗi khi khởi tạo SDL_ttf: " << TTF_GetError() << std::endl;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_Log("SDL Mixer could not initialize! SDL_mixer Error: %s", Mix_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(m_Renderer == nullptr) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    PushState(new Menu());

    return m_IsRunning = true;
}

void Engine::Render()
{
    if (!m_States.empty()) {
        m_States.back()->Render();
    }
}

void Engine::Update()
{
    if (!m_States.empty()) {
        float dt = Timer::GetInstance()->GetDeltaTime();
        m_States.back()->Update(dt);
    }
}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}

bool Engine::Clean()
{
    while (!m_States.empty()) {
        m_States.back()->Exit();
        delete m_States.back();
        m_States.pop_back();
    }
    TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    TTF_Quit();
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();
}

void Engine::Quit()
{
    m_IsRunning = false;
}

void Engine::PushState(GameState* state) {
    m_States.push_back(state);
    state->Enter();
}

void Engine::PopState() {
    if (!m_States.empty()) {
        m_States.back()->Exit();
        delete m_States.back();
        m_States.pop_back();
    }
}

void Engine::ChangeState(GameState* state) {
    if (!m_States.empty()) {
        m_States.back()->Exit();
        delete m_States.back();
        m_States.pop_back();
    }
    m_States.push_back(state);
    state->Enter();
}
