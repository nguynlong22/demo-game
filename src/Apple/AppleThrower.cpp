#include "AppleThrower.h"
#include "Collision.h"
#include "Engine.h"
#include "Warrior.h"
#include <cstdlib>
#include <ctime>

AppleThrower::AppleThrower() {
    std::srand(std::time(nullptr));
}

void AppleThrower::Update(float dt, const SDL_Rect& swordRect) {
    timeSinceLastThrow += dt;
    if (timeSinceLastThrow >= throwInterval) {
        ThrowApple();
        timeSinceLastThrow = 0.0f;
    }

    Warrior* player = Engine::GetInstance()->GetPlayer();
    SDL_Rect warriorCollider = player->GetCollider();

    for (auto it = apples.begin(); it != apples.end();) {
        Apple* apple = *it;
        apple->Update(dt);

        // Kiểm tra nếu chém trúng
        /*if (!apple->isCut && Collision::CheckCollision(apple->GetRect(), swordRect)) {
            apple->Cut();
            delete apple;
            it = apples.erase(it);
            continue;
        }*/

        if (!apple->isCut && Collision::CheckCollision(apple->GetRect(), warriorCollider)) {
            apple->isMissed = true; // Táo chạm Warrior
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
