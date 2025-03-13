#ifndef APPLE_H
#define APPLE_H

#include "GameObject.h"
#include "Vector2D.h"
#include "TextureManager.h"

class Fruit : public GameObject  // Kế thừa GameObject
{
public:
    Vector2D velocity;
    int m_PointValue;
    bool isMissed = false;

    Fruit(Properties* props, Vector2D vel, int pointValue);

    void Update(float dt) override;  // Ghi đè từ GameObject
    void Draw() override;            // Ghi đè từ GameObject
    void Clean() override;
    SDL_Rect GetRect();
    int GetPointValue() { return m_PointValue; }
};

#endif // APPLE_H
