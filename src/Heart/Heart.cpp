#include "Heart.h"
#include "TextureManager.h"
#include "Engine.h"

Heart::Heart(int maxHearts) : m_MaxHearts(maxHearts), m_Hearts(maxHearts) {}

void Heart::LoseHeart() {
    if (m_Hearts > 0) {
        m_Hearts--;
    }
}

void Heart::Draw() {
    SDL_Renderer* renderer = Engine::GetInstance()->GetRenderer();
    for (int i = 0; i < m_Hearts; i++) {
        // Vẽ biểu tượng trái tim (giả định texture "heart")
        TextureManager::GetInstance()->Draw("heart", 10 + i * 40, 50, 64, 64);
    }
}
