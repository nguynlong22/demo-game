#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "Engine.h"


Warrior::Warrior(Properties* props): Character(props)
{
    m_RigidBody = new RigidBody();
    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 6, 80);
}

void Warrior::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Warrior::Update(float dt) {
    m_Animation->SetProps("player_run", 1, 8, 60);

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
        m_Animation->SetProps("player_attack1", 1, 6, 45);
    }

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S)) {
        m_Animation->SetProps("player_attack2", 1, 5, 45);
    }

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)) {
        m_Animation->SetProps("player_attack3", 1, 6, 45);
    }

    m_RigidBody->Update(dt);

    m_Animation->Update();
}

SDL_Rect Warrior::GetSwordHitbox() {
    int swordWidth = 50;  // Chiều rộng kiếm
    int swordHeight = 20; // Chiều cao kiếm
    int offsetX = GetWidth();

    return { GetX() + offsetX, GetY() + 20, swordWidth, swordHeight };
}

void Warrior::Clean()
{
    TextureManager::GetInstance()->Clean();
}
