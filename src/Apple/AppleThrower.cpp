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

    throwInterval = 100.0f - (realTime * 0.05f);
    if (throwInterval < minThrowInterval) {
        throwInterval = minThrowInterval;
    }

    if (timeSinceLastThrow >= throwInterval) {
        ThrowFruit();
        timeSinceLastThrow = 0.0f;
    }

    Warrior* player = m_PlayState->GetPlayer();
    SDL_Rect warriorCollider = player->GetCollider();

    for (auto it = fruits.begin(); it != fruits.end();) {
        Fruit* fruit = *it;
        fruit->Update(dt);
        if (Collision::CheckCollision(fruit->GetRect(), warriorCollider)) {
            m_PlayState->AddScore(fruit->GetPointValue());
            delete fruit;
            it = fruits.erase(it);
            continue;
        }
        if (fruit->GetRect().y > SCREEN_HEIGHT) {
            fruit->isMissed = true;
        }
        if (fruit->isMissed) {
            m_PlayState->LoseHeart();
            delete fruit;
            it = fruits.erase(it);
        } else {
            ++it;
        }
    }
}

void FruitThrower::ThrowFruit() {
    int randomX = std::rand() % (SCREEN_WIDTH - 64);
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
