#include "Play.h"
#include "Engine.h"
#include "Input.h"
#include "TextureManager.h"

PlayState::PlayState() {
    player = new Warrior(new Properties("player", 100, 420, 128, 128));
    appleThrower = new AppleThrower(player);
}

PlayState::~PlayState() {
    delete player;
    delete appleThrower;
}

void PlayState::Update(float dt) {
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)) {
        Engine::GetInstance()->PopState(); // Quay lại Menu
    }
    player->Update(dt);
    appleThrower->Update(dt, player->GetCollider());
}

void PlayState::Render() {
    SDL_Renderer* renderer = Engine::GetInstance()->GetRenderer();
    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Nền xanh trời
    SDL_RenderClear(renderer);
    TextureManager::GetInstance()->Draw("bg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    player->Draw();
    appleThrower->Draw();
    SDL_RenderPresent(renderer);
}

void PlayState::Enter() {
    TextureManager::GetInstance()->Load("bg", "assets/background.png");
    TextureManager::GetInstance()->Load("player", "assets/IDLE.png");
    TextureManager::GetInstance()->Load("player_run", "assets/RUN.png");
    TextureManager::GetInstance()->Load("apple", "assets/apple.png");
}

void PlayState::Exit() {
    // Texture sẽ được dọn dẹp trong Engine::Clean()
}
