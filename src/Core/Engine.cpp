#include "Engine.h"
#include "TextureManager.h"
#include "AppleThrower.h"
#include "Warrior.h"
#include "Input.h"
#include "SDL.h"
#include "Timer.h"
//#include "Background.h"

Engine* Engine::s_Instance = nullptr;
//Warrior* player = nullptr;
//Background* m_Background = nullptr;
AppleThrower* appleThrower = nullptr;

bool Engine::Init()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    m_Window = SDL_CreateWindow("Soft Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(m_Window == nullptr) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(m_Renderer == nullptr) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    TextureManager::GetInstance()->Load("player", "assets/IDLE.png");
    TextureManager::GetInstance()->Load("player_run", "assets/RUN.png");
    TextureManager::GetInstance()->Load("player_attack1", "assets/ATTACK 1.png");
    TextureManager::GetInstance()->Load("player_attack2", "assets/ATTACK 2.png");
    TextureManager::GetInstance()->Load("player_attack3", "assets/ATTACK 3.png");
    TextureManager::GetInstance()->Load("bg", "assets/background.png");
    TextureManager::GetInstance()->Load("apple", "assets/apple.png");

    player = new Warrior(new Properties("player", 100, 420, 128, 128));
    appleThrower = new AppleThrower();

    return m_IsRunning = true;
}

void Engine::Render()
{
    SDL_RenderClear(m_Renderer);
    TextureManager::GetInstance()->Draw("bg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    player->Draw();
    appleThrower->Draw();
    SDL_RenderPresent(m_Renderer);
}

void Engine::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    player->Update(dt);
    //m_Background->Update(dt);
    appleThrower->Update(dt, player->GetCollider());
}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}

bool Engine::Clean()
{
    //delete m_Background;
    delete appleThrower;
    delete player;
    TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
}

void Engine::Quit()
{
    m_IsRunning = false;
}
