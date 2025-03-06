#ifndef COLLISION_H
#define COLLISION_H
#include "SDL.h"

class Collision
{
    public:
        static bool CheckCollision(const SDL_Rect& a, const SDL_Rect& b) {
        return (a.x < b.x + b.w && a.x + a.w > b.x &&
                a.y < b.y + b.h && a.y + a.h > b.y);
    }
};
#endif // COLLISION_H
