#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "SDL.h"
#include "TextureManager.h"

class Background {
    public:
        Background(const char* textureID, int speed);
        void Update();
        void Render();

    private:
        int m_Speed;
        SDL_Rect m_SrcRect, m_DestRect;
        int m_Width, m_Height;
        int m_X1, m_X2;
        std::string m_TextureID;
};

#endif // BACKGROUND_H
