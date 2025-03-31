#ifndef APPLE_H
#define APPLE_H

#include "GameObject.h"
#include "Vector2D.h"
#include "TextureManager.h"

class Fruit : public GameObject
{
public:
    Vector2D velocity;
    bool isMissed = false;

    Fruit(Properties* props, Vector2D vel, int pointValue, bool isBomb);

    void Update(float dt) override;
    void Draw() override;
    void Clean() override;

    SDL_Rect GetRect();
    int GetPointValue() { return m_PointValue; }
    bool IsBomb() { return isBomb; }

private:
    int m_PointValue;
    bool isBomb;
};

#endif // APPLE_H
