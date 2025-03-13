#include "Apple.h"
#include "Engine.h"
#include "TextureManager.h"
#include "RigidBody.h"

Fruit::Fruit(Properties* props, Vector2D vel, int pointValue) : GameObject(props), velocity(vel), m_PointValue(pointValue) {}

void Fruit::Update(float dt) {
    if (!isMissed) {
        m_Transform->TranslateX(velocity.X * dt);
        m_Transform->TranslateY(velocity.Y * dt);
    }

    // Kiểm tra nếu táo vượt khỏi màn hình
    if (m_Transform->Y > SCREEN_HEIGHT || m_Transform->X < 0 || m_Transform->X > SCREEN_WIDTH) {
        isMissed = true;
    }
}

SDL_Rect Fruit::GetRect() {
    return { (int)m_Transform->X + 10, (int)m_Transform->Y + 10, 44, 44 }; // Giảm 10px từ mỗi cạnh
}

void Fruit::Draw() {
    TextureManager::GetInstance()->Draw(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height);
    SDL_Rect hitbox = GetRect();
    SDL_Renderer* renderer = Engine::GetInstance()->GetRenderer();

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // RGBA: Đỏ, không trong suốt
    SDL_RenderDrawRect(renderer, &hitbox);

    // Đặt lại màu về mặc định (tránh ảnh hưởng render khác)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Màu đen hoặc tùy chỉnh
}
void Fruit::Clean() {
}
