#include "Apple.h"
#include "Engine.h"
#include "TextureManager.h"
#include "RigidBody.h"

Apple::Apple(Properties* props, Vector2D vel) : GameObject(props), velocity(vel) {}

void Apple::Update(float dt) {
    if (!isCut) {
        m_Transform->TranslateX(velocity.X * dt);
        m_Transform->TranslateY(velocity.Y * dt);
    }

    // Kiểm tra nếu táo vượt khỏi màn hình
    if (m_Transform->Y > SCREEN_HEIGHT || m_Transform->X < 0 || m_Transform->X > SCREEN_WIDTH) {
        isMissed = true;
    }
}

void Apple::Cut() {
    isCut = true;
}

SDL_Rect Apple::GetRect() {
    return { (int)m_Transform->X + 10, (int)m_Transform->Y + 10, 44, 44 }; // Giảm 10px từ mỗi cạnh
}

void Apple::Draw() {
    TextureManager::GetInstance()->Draw(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height);
}
void Apple::Clean() {
}
