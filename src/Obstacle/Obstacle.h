#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "SDL.h"
#include "TextureManager.h"
#include "Vector2D.h"

class Obstacle {
public:
    Obstacle(const char* textureID, int x, int y, int speed);
    void Update();
    void Render();
    bool IsOffScreen();

    SDL_Rect GetCollider() { return m_DestRect; }

private:
    int m_Speed;
    SDL_Rect m_SrcRect, m_DestRect;
    std::string m_TextureID;
};

#endif
