#ifndef APPLETHROWER_H
#define APPLETHROWER_H
#include "Apple.h"
#include "Warrior.h"
#include <vector>

class PlayState;

class AppleThrower {
private:
    std::vector<Apple*> apples;
    float throwInterval = 80.0f;        // Khoảng cách ban đầu giữa các lần spawn
    float minThrowInterval = 10.0f;     // Giới hạn nhỏ nhất của throwInterval
    float timeSinceLastThrow = 0.0f;   // Thời gian kể từ lần spawn cuối
    float totalTime = 0.0f;
    PlayState* m_PlayState;
public:
    AppleThrower(PlayState* playState);
    void Update(float dt, const SDL_Rect& p);
    void ThrowApple();
    void Draw();

};

#endif // APPLETHROWER_H
