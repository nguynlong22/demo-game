#include "Engine.h"
#include "TextureManager.h"

#include "Warrior.h"
#include "Input.h"
#include "SDL.h"
#include "Timer.h"

Engine* Engine::s_Instance = nullptr;
Warrior* player = nullptr;


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

    TextureManager::GetInstance()->Load("player", "assets/Idle.png");
    TextureManager::GetInstance()->Load("player_run", "assets/Walk.png");
    TextureManager::GetInstance()->Load("player_jump", "assets/Jump.png");
    TextureManager::GetInstance()->Load("bg", "assets/bg.png");
    m_Background = new Background("bg", 2);
    TextureManager::GetInstance()->Load("obstacle", "assets/obstacle.png");

    m_Obstacles.push_back(new Obstacle("obstacle", 800, 500, 50, 50, 3));  // X=800, Y=500, Width=50, Height=50, Speed=3
    m_Obstacles.push_back(new Obstacle("obstacle", 1200, 500, 50, 50, 3)); // Chướng ngại vật thứ 2

    player = new Warrior(new Properties("player", 100, 400, 128, 128));

    return m_IsRunning = true;
}

void Engine::Render()
{
    SDL_RenderClear(m_Renderer);

    player->Draw();


    m_Background->Render();

    for (auto& obstacle : m_Obstacles) {
        obstacle->Render();
    }
    SDL_RenderPresent(m_Renderer);
}

void Engine::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    player->Update(dt);
    m_Background->Update();

    // Cập nhật danh sách obstacle
    for (auto it = m_Obstacles.begin(); it != m_Obstacles.end();) {
        (*it)->Update();
        if ((*it)->IsOffScreen()) {
            delete *it;
            it = m_Obstacles.erase(it);
        } else {
            ++it;
        }
    }

    // Sinh obstacle mỗi 2 giây
    m_SpawnTimer += Timer::GetInstance()->GetDeltaTime();
    if (m_SpawnTimer >= 2.0f) {
        int yPosition = 400;  // Vị trí của chướng ngại vật trên mặt đất
        m_Obstacles.push_back(new Obstacle("obstacle_texture", 800, yPosition, 5));
        m_SpawnTimer = 0.0f;
    }
}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}

bool Engine::Clean()
{
    delete m_Background;

    for (auto& obstacle : m_Obstacles) {
        delete obstacle;
    }
    m_Obstacles.clear();
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
