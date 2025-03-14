#ifndef APPLETHROWER_H
#define APPLETHROWER_H
#include "Apple.h"
#include "Warrior.h"
#include <vector>

class PlayState;

class FruitThrower {
private:
    std::vector<Fruit*> fruits;
    float throwInterval = 50.0f;
    float minThrowInterval = 10.0f;
    float timeSinceLastThrow = 0.0f;
    PlayState* m_PlayState;
public:
    FruitThrower(PlayState* playState);
    void Update(float dt);
    void ThrowFruit();
    void Draw();

};

#endif // APPLETHROWER_H
