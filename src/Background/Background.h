/*#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "GameObject.h"
#include "TextureManager.h"

class Background : public GameObject {
public:
    Background(Properties* props, int scrollSpeed) : GameObject(props), m_ScrollSpeed(scrollSpeed) {
        m_ScrollX = 0;
    }

    void Update(float dt) override {
        m_ScrollX -= m_ScrollSpeed * dt;
        if (m_ScrollX <= -m_Width) {
            m_ScrollX = 0; // Reset vị trí khi cuộn hết màn hình
        }
    }

    void Draw() override {
        // Vẽ hình ảnh chính
        TextureManager::GetInstance()->Draw(m_TextureID, m_ScrollX, 0, m_Width, m_Height);
        // Vẽ hình ảnh tiếp theo để tạo hiệu ứng lặp
        TextureManager::GetInstance()->Draw(m_TextureID, m_ScrollX + m_Width, 0, m_Width, m_Height);
    }

    void Clean() override {}

private:
    float m_ScrollX;
    int m_ScrollSpeed;
};

#endif/*
