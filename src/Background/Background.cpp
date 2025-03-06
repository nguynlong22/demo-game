#include "Background.h"
#include "TextureManager.h"
#include "Engine.h"

Background::Background(const char* textureID, int speed) {
    m_TextureID = textureID;
    m_Speed = speed;

    if (!TextureManager::GetInstance()->GetTexture(m_TextureID)) {
        TextureManager::GetInstance()->Load(m_TextureID, "assets/bg.png");
    }

    SDL_Texture* texture = TextureManager::GetInstance()->GetTexture(m_TextureID);
    SDL_QueryTexture(texture, nullptr, nullptr, &m_Width, &m_Height);

    m_X1 = 0;
    m_X2 = m_Width;
}
