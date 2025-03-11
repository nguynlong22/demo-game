#ifndef APPLETHROWER_H
#define APPLETHROWER_H
#include "Apple.h"
#include "Warrior.h"
#include <vector>

class AppleThrower {
private:
    std::vector<Apple*> apples;
    float throwInterval = 50.0f;
    float timeSinceLastThrow = 0.0f;
    Warrior* player;
public:
    AppleThrower(Warrior *p);
    void Update(float dt, const SDL_Rect& p);
    void ThrowApple();
    void Draw();

};

#endif // APPLETHROWER_H
