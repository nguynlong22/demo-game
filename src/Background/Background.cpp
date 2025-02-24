#include "Background.h"
#include "TextureManager.h"
#include "Engine.h"

Background::Background(const char* textureID, int speed) {
    m_TextureID = textureID;
    m_Speed = speed;

    // Load texture trước khi sử dụng
    if (!TextureManager::GetInstance()->Load(m_TextureID, "assets/bg.png")) {
        SDL_Log("Failed to load background texture!");
    }

    // Lấy kích thước của texture
    SDL_Texture* texture = TextureManager::GetInstance()->m_TextureMap[m_TextureID];
    SDL_QueryTexture(texture, nullptr, nullptr, &m_Width, &m_Height);

    // Khởi tạo vị trí 2 background để tạo hiệu ứng cuộn vô hạn
    m_X1 = 0;
    m_X2 = m_Width;

    m_SrcRect = {0, 0, m_Width, m_Height};
    m_DestRect = {0, 0, m_Width, m_Height};
}

void Background::Update() {
    // Di chuyển background từ phải sang trái
    m_X1 -= m_Speed;
    m_X2 -= m_Speed;

    // Khi background ra khỏi màn hình, đặt lại vị trí bên phải
    if (m_X1 + m_Width <= 0) {
        m_X1 = m_X2 + m_Width;
    }
    if (m_X2 + m_Width <= 0) {
        m_X2 = m_X1 + m_Width;
    }
}

void Background::Render() {
    // Vẽ hai background nối tiếp nhau để tạo hiệu ứng cuộn
    m_DestRect.x = m_X1;
    TextureManager::GetInstance()->Draw(m_TextureID, m_DestRect.x, m_DestRect.y, m_Width, m_Height);

    m_DestRect.x = m_X2;
    TextureManager::GetInstance()->Draw(m_TextureID, m_DestRect.x, m_DestRect.y, m_Width, m_Height);
}
