#include "AppleThrower.h"
#include "Collision.h"
#include "Engine.h"
#include "Warrior.h"
#include "Play.h"
#include <cstdlib>
#include <ctime>

AppleThrower::AppleThrower(PlayState* playState) : m_PlayState(playState) {
    std::srand(std::time(nullptr));
}

void AppleThrower::Update(float dt, const SDL_Rect& p) {
    totalTime += dt; // Cộng dồn thời gian chơi
    timeSinceLastThrow += dt;
    std::cout << "dt: " << dt << std::endl;

    // Giảm throwInterval theo thời gian (tuyến tính)
    throwInterval = 50.0f - (totalTime * 0.2f); // Giảm 0.05 mỗi giây
    if (throwInterval < minThrowInterval) {
        throwInterval = minThrowInterval; // Giới hạn tối thiểu
    }

    if (timeSinceLastThrow >= throwInterval) {
        ThrowApple();
        timeSinceLastThrow = 0.0f;
    }

    Warrior* player = m_PlayState->GetPlayer();
    SDL_Rect warriorCollider = player->GetCollider();

    for (auto it = apples.begin(); it != apples.end();) {
        Apple* apple = *it;
        apple->Update(dt);
        if (!apple->isCut && Collision::CheckCollision(apple->GetRect(), warriorCollider)) {
            apple->isMissed = true;
            m_PlayState->AddScore(10);
        }
        // Xóa táo nếu nó bị bỏ lỡ
        if (apple->isMissed) {
            delete apple;
            it = apples.erase(it);
        } else {
            ++it;
        }
    }
}

void AppleThrower::ThrowApple() {
    int randomX = std::rand() % (SCREEN_WIDTH - 64);
    Vector2D startPos(randomX, 0); // Y = 0 (trên cùng màn hình)
    Vector2D velocity(0, 2); // Rơi thẳng xuống với tốc độ 10 pixel/s

    Properties* appleProps = new Properties("apple", startPos.X, startPos.Y, 64, 64);
    apples.push_back(new Apple(appleProps, velocity));
}

void AppleThrower::Draw() {
    for (auto* apple : apples) {
        apple->Draw();
    }
}
