#include "AppleThrower.h"
#include "Collision.h"
#include "Engine.h"
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

    for (auto it = apples.begin(); it != apples.end();) {
        Apple* apple = *it;
        apple->Update(dt);

        // Kiểm tra nếu chém trúng
        if (!apple->isCut && Collision::CheckCollision(apple->GetRect(), swordRect)) {
            apple->Cut();
            delete apple;
            it = apples.erase(it);
            continue;
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
    int direction = std::rand() % 3;
    Vector2D startPos;
    Vector2D velocity;

    switch (direction) {
        case 0: // Táo rơi từ trên xuống
            startPos = Vector2D(170, 0);
            velocity = Vector2D(0, 10);
            break;
        case 1: // Táo bay từ trái qua
            startPos = Vector2D(960, 450);
            velocity = Vector2D(-10, 0);
            break;
        case 2: // Táo bay từ phải qua
            startPos = Vector2D(960, 490);
            velocity = Vector2D(-10, 0);
            break;
    }

    // ✅ Tạo `Properties` để phù hợp với `Apple` mới
    Properties* appleProps = new Properties("apple", startPos.X, startPos.Y, 64, 64);
    apples.push_back(new Apple(appleProps, velocity));
}

void AppleThrower::Draw() {
    for (auto* apple : apples) {
        apple->Draw();
    }
}
