#include "Play.h"
#include "Engine.h"
#include "Input.h"
#include "TextureManager.h"

bool PlayState::hasPlayed = false;

PlayState::PlayState() {
    player1 = new Warrior(new Properties("player", 100, 600, 128, 128));
    player2 = new Warrior(new Properties("player", 600, 600, 128, 128));
    fruitThrower = new FruitThrower(this);
    hearts1 = new Heart(5); // Khởi tạo 5 mạng
    hearts2 = new Heart(5);
    hasPlayed = true;
    score1 = 0;
    score2 = 0;
    activeSide = 0;
    showTutorial = true;      // Bật hướng dẫn khi bắt đầu
    tutorialTimer = 100.0f;     // 5 giây
}

void PlayState::Update(float dt) {
    if (showTutorial) {
        tutorialTimer -= dt;
        if (tutorialTimer <= 0.0f) {
            showTutorial = false; // Tắt hướng dẫn sau 5 giây
        }
        return; // Không cập nhật game khi đang hiển thị hướng dẫn
    }

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)) {
        Engine::GetInstance()->PushState(new Menu()); // ESC để quay lại Menu
    }

    if (hearts1->IsGameOver() && !hearts2->IsGameOver()) {
        activeSide = 2; // Chỉ bên Player 2
    } else if (hearts2->IsGameOver() && !hearts1->IsGameOver()) {
        activeSide = 1; // Chỉ bên Player 1
    } else if (hearts1->IsGameOver() && hearts2->IsGameOver()) {
        int winner = (score2 > score1) ? 2 : 1;
        Engine::GetInstance()->PushState(new GameOver(score1, score2, winner));
        return; // Dừng cập nhật khi cả hai hết mạng
    } else {
        activeSide = 0; // Cả hai bên
    }

    player1->Update(dt);
    player2->Update(dt);
    fruitThrower->Update(dt);
}

void PlayState::Render() {
    SDL_Renderer* renderer = Engine::GetInstance()->GetRenderer();
    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Nền xanh trời
    SDL_RenderClear(renderer);
    TextureManager::GetInstance()->Draw("bg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Màu trắng
    SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT);

    player1->Draw();
    player2->Draw();

    hearts1->Draw1();
    hearts2->Draw2();

    fruitThrower->Draw();

    std::string scoreText1 = "P1 Score: " + std::to_string(score1);
    TextureManager::GetInstance()->DrawText(scoreText1, 10, 10, 255, 255, 255);

    // Hiển thị điểm Player 2
    std::string scoreText2 = "P2 Score: " + std::to_string(score2);
    TextureManager::GetInstance()->DrawText(scoreText2, SCREEN_WIDTH - 200, 10, 255, 255, 255);

    if (hearts1->IsGameOver()) {
        TextureManager::GetInstance()->DrawText("Game Over", 200, SCREEN_HEIGHT / 2, 255, 0, 0); // Nửa trái, màu đỏ
    }
    if (hearts2->IsGameOver()) {
        TextureManager::GetInstance()->DrawText("Game Over", 650, SCREEN_HEIGHT / 2, 255, 0, 0); // Nửa phải, màu đỏ
    }

    if (showTutorial) {
    // Hướng dẫn Player 1 (bên trái)
        TextureManager::GetInstance()->DrawText("A/D de di chuyen",
            SCREEN_WIDTH / 4 - 80, SCREEN_HEIGHT / 2 - 10, 255, 0, 0);

    // Hướng dẫn Player 2 (bên phải)
        TextureManager::GetInstance()->DrawText("</> de di chuyen",
            3 * SCREEN_WIDTH / 4 - 80, SCREEN_HEIGHT / 2 - 10, 255, 0, 0);
    }
    SDL_RenderPresent(renderer);
}

void PlayState::Enter() {
    TextureManager::GetInstance()->Load("bg", "assets/background.png");

    TextureManager::GetInstance()->Load("player1", "assets/Idle1.png");
    TextureManager::GetInstance()->Load("player_run1", "assets/Run1.png");
    TextureManager::GetInstance()->Load("player2", "assets/Idle2.png");
    TextureManager::GetInstance()->Load("player_run2", "assets/Run2.png");

    TextureManager::GetInstance()->Load("apple", "assets/apple.png");
    TextureManager::GetInstance()->Load("lemonade", "assets/lemonade.png");
    TextureManager::GetInstance()->Load("orange", "assets/orange.png");
    TextureManager::GetInstance()->Load("banana", "assets/banana.png");
    TextureManager::GetInstance()->Load("bomb", "assets/bomb.png");

    TextureManager::GetInstance()->Load("heart", "assets/heart.png");
    TextureManager::GetInstance()->LoadFont("assets/arial.ttf", 32);

    pickupSound = Mix_LoadWAV("assets/pickUpSound.mp3");
    if (!pickupSound) {
        SDL_Log("Failed to load pickup sound! SDL_mixer Error: %s", Mix_GetError());
    }
    fruitThrower->SetPickupSound(pickupSound);
}

void PlayState::AddScorePlayer1(int points) {
    score1 += points;
}

void PlayState::AddScorePlayer2(int points) {
    score2 += points;
}

void PlayState::LoseHeartPlayer1() {
    hearts1->LoseHeart();
}

void PlayState::LoseHeartPlayer2() {
    hearts2->LoseHeart();
}


PlayState::~PlayState() {
    delete player1;
    delete player2;
    delete fruitThrower;
    delete hearts1;
    delete hearts2;
    if (pickupSound) Mix_FreeChunk(pickupSound);
}
