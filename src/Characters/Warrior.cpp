#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "Engine.h"
#include "Obstacle.h"

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

void Warrior::Update(float dt)
{
    m_Animation->SetProps("player", 1, 6, 80);
    m_RigidBody->UnsetForce();

    // Di chuyển trái
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)){
        m_RigidBody->ApplyForceX(5 * BACKWARD);
        m_Animation->SetProps("player_run", 1, 8, 80, SDL_FLIP_HORIZONTAL);
    }

    // Di chuyển phải
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){
        m_RigidBody->ApplyForceX(5 * FORWARD);
        m_Animation->SetProps("player_run", 1, 8, 80);
    }

    for (auto& obstacle : Engine::GetInstance()->GetObstacles()) {
        if (SDL_HasIntersection(&m_Collider, &obstacle->GetCollider())) {
            std::cout << "Collision detected!" << std::endl;
            // Xử lý game over hoặc trừ máu
        }
    }

    m_RigidBody->Update(dt);

    // Cập nhật vị trí nhân vật
    m_Transform->TranslateX(m_RigidBody->Postition().X);
    //m_Transform->TranslateY(m_RigidBody->Postition().Y);

    m_Animation->Update();
}

void Warrior::Clean()
{
    TextureManager::GetInstance()->Clean();
}





