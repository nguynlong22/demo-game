#ifndef COLLISION_H
#define COLLISION_H

#include "SDL.h"

class Collision {
public:
    static bool CheckCollision(const SDL_Rect& a, const SDL_Rect& b) {
        bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
        bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
        return (x_overlaps && y_overlaps);
    }
};

#endif // COLLISION_H
