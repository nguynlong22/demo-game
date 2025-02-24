#include "Obstacle.h"
#include "TextureManager.h"
#include "Engine.h"

Obstacle::Obstacle(const char* textureID, int x, int y, int width, int height, int speed) {
    m_TextureID = textureID;
    m_Speed = speed;
    m_X = x;
    m_Y = y;
    m_Width = width;
    m_Height = height;

    // Load texture nếu chưa có
    if (!TextureManager::GetInstance()->Load(m_TextureID, "assets/obstacle.png")) {
        SDL_Log("Failed to load obstacle texture!");
    }
}

void Obstacle::Update() {
    // Di chuyển chướng ngại vật sang trái
    m_X -= m_Speed;

    // Nếu chướng ngại vật ra khỏi màn hình, reset vị trí
    if (m_X + m_Width < 0) {
        m_X = Engine::GetInstance()->GetScreenWidth();  // Đặt lại vị trí bên phải màn hình
    }
}

void Obstacle::Render() {
    // Vẽ chướng ngại vật tại vị trí hiện tại
    TextureManager::GetInstance()->Draw(m_TextureID, m_X, m_Y, m_Width, m_Height);
}
