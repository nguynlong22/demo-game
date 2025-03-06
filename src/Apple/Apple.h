#ifndef APPLE_H
#define APPLE_H

#include "GameObject.h"
#include "Vector2D.h"
#include "TextureManager.h"

class Apple : public GameObject  // Kế thừa GameObject
{
public:
    Vector2D velocity;
    bool isCut = false;
    bool isMissed = false;

    Apple(Properties* props, Vector2D vel);

    void Update(float dt) override;  // Ghi đè từ GameObject
    void Draw() override;            // Ghi đè từ GameObject
    void Clean() override;
    void Cut();
    SDL_Rect GetRect();
};

#endif // APPLE_H
