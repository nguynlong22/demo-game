#include "Play.h"
#include "Engine.h"
#include "Input.h"
#include "TextureManager.h"

bool PlayState::hasPlayed = false;

PlayState::PlayState() {
    player = new Warrior(new Properties("player", 100, 420, 128, 128));
    fruitThrower = new FruitThrower(this);
    hearts = new Heart(5); // Khởi tạo 5 mạng
    hasPlayed = true;
    score = 0;
}

PlayState::~PlayState() {
    delete player;
    delete fruitThrower;
    delete hearts;
}

void PlayState::Update(float dt) {
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)) {
        Engine::GetInstance()->PushState(new Menu()); // Quay lại Menu
    }

    if (hearts->IsGameOver()) {
        Engine::GetInstance()->PushState(new Menu()); // Quay lại Menu khi hết mạng
        // Có thể thêm GameOverState nếu muốn
    }

    player->Update(dt);
    fruitThrower->Update(dt);
}

void PlayState::Render() {
    SDL_Renderer* renderer = Engine::GetInstance()->GetRenderer();
    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Nền xanh trời
    SDL_RenderClear(renderer);
    TextureManager::GetInstance()->Draw("bg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    player->Draw();
    fruitThrower->Draw();
    hearts->Draw(); // Vẽ trái tim

    std::string scoreText = "Score: " + std::to_string(score);
    TextureManager::GetInstance()->DrawText(scoreText, 10, 10, 255, 255, 255);

    SDL_RenderPresent(renderer);
}

void PlayState::Enter() {
    TextureManager::GetInstance()->Load("bg", "assets/background.png");
    TextureManager::GetInstance()->Load("player", "assets/IDLE.png");
    TextureManager::GetInstance()->Load("player_run", "assets/RUN.png");
    TextureManager::GetInstance()->Load("apple", "assets/apple.png");
    TextureManager::GetInstance()->Load("lemonade", "assets/lemonade.png");
    TextureManager::GetInstance()->Load("orange", "assets/orange.png");
    TextureManager::GetInstance()->Load("banana", "assets/banana.png");
    TextureManager::GetInstance()->Load("heart", "assets/heart.png");
    TextureManager::GetInstance()->LoadFont("assets/arial.ttf", 32);
}

void PlayState::AddScore(int points) {
    score += points;
}

void PlayState::LoseHeart() {
    hearts->LoseHeart(); // Định nghĩa hàm, giảm 1 mạng
}

void PlayState::Exit() {
    // Texture sẽ được dọn dẹp trong Engine::Clean()
}
