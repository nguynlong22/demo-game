#include "AppleThrower.h"
#include "Collision.h"
#include "Engine.h"
#include "Warrior.h"
#include "Play.h"
#include "Heart.h"
#include <cstdlib>
#include <ctime>

FruitThrower::FruitThrower(PlayState* playState) : m_PlayState(playState) {
    std::srand(std::time(nullptr));
}

void FruitThrower::Update(float dt) {
    float realTime = SDL_GetTicks() / 1000.0f;
    timeSinceLastThrow += dt;

    throwInterval = 50.0f - (realTime * 0.05f);
    if (throwInterval < minThrowInterval) {
        throwInterval = minThrowInterval;
    }

    if (timeSinceLastThrow >= throwInterval) {
        ThrowFruit();
        timeSinceLastThrow = 0.0f;
    }

    Warrior* player1 = m_PlayState->GetPlayer();   // Player 1
    Warrior* player2 = m_PlayState->GetPlayer2();  // Player 2
    SDL_Rect warriorCollider1 = player1->GetCollider();
    SDL_Rect warriorCollider2 = player2->GetCollider();

    for (auto it = fruits.begin(); it != fruits.end();) {
        Fruit* fruit = *it;
        fruit->Update(dt);

        if (Collision::CheckCollision(fruit->GetRect(), warriorCollider1)) {
            m_PlayState->AddScorePlayer1(fruit->GetPointValue());
            if (m_PickupSound) Mix_PlayChannel(-1, m_PickupSound, 0);
            delete fruit;
            it = fruits.erase(it);
            continue;
        }

        if (Collision::CheckCollision(fruit->GetRect(), warriorCollider2)) {
            m_PlayState->AddScorePlayer2(fruit->GetPointValue());
            if (m_PickupSound) Mix_PlayChannel(-1, m_PickupSound, 0);
            delete fruit;
            it = fruits.erase(it);
            continue;
        }

        if (fruit->GetRect().y > SCREEN_HEIGHT) {
            fruit->isMissed = true;

            if (fruit->GetRect().x < SCREEN_WIDTH / 2) {
                m_PlayState->LoseHeartPlayer1(); // Player 1 bỏ lỡ
            } else {
                m_PlayState->LoseHeartPlayer2(); // Player 2 bỏ lỡ
            }
            delete fruit;
            it = fruits.erase(it);
        } else {
            ++it;
        }
    }
}

void FruitThrower::ThrowFruit() {
    int halfScreen = SCREEN_WIDTH / 2;
    int randomX;
    int activeSide = m_PlayState->GetActiveSide();

    if (activeSide == 0) {
        randomX = 50 + rand() % (920 - 50 + 1); // Cả hai bên
    } else if (activeSide == 1) {
        randomX = 50 + rand() % (450 - 50 + 1); // Chỉ bên trái
    } else {
        randomX = 500 + rand() % (920 - 500 + 1); // Chỉ bên phải
    }

    Vector2D startPos(randomX, 0);
    Vector2D velocity(0, 0);

    // Chọn ngẫu nhiên loại quả với xác suất tùy chỉnh
    int fruitType = std::rand() % 10; // Phạm vi 0-9
    Properties* fruitProps = nullptr;
    int pointValue = 0;

    if (fruitType >= 0 && fruitType < 4) { // 0-3: Táo (40%)
        fruitProps = new Properties("apple", startPos.X, startPos.Y, 64, 64);
        pointValue = 10;
        velocity.Y = 2.0f; // Táo rơi chậm
    }
    else if (fruitType >= 4 && fruitType < 6) { // 4-5: Chanh (20%)
        fruitProps = new Properties("lemonade", startPos.X, startPos.Y, 64, 64);
        pointValue = 15; // Điểm trung bình
        velocity.Y = 3.0f; // Chanh rơi hơi nhanh hơn táo
    }
    else if (fruitType >= 6 && fruitType < 8) { // 6-7: Cam (20%)
        fruitProps = new Properties("orange", startPos.X, startPos.Y, 64, 64);
        pointValue = 20;
        velocity.Y = 4.0f; // Cam rơi vừa
    }
    else { // 8-9: Chuối (20%)
        fruitProps = new Properties("banana", startPos.X, startPos.Y, 64, 64);
        pointValue = 30; // Điểm cao hơn cam
        velocity.Y = 5.0f; // Chuối rơi nhanh hơn cam
    }

    fruits.push_back(new Fruit(fruitProps, velocity, pointValue));
}

void FruitThrower::Draw() {
    for (auto* fruit : fruits) {
        fruit->Draw();
    }
}
