    #include "Warrior.h"
    #include "TextureManager.h"
    #include "SDL.h"
    #include "Input.h"
    #include "Engine.h"


    Warrior::Warrior(Properties* props): Character(props)
    {
        m_Collider = new Collider();
        m_Collider->SetBuffer(20 , 50, -20, 0);
        m_RigidBody = new RigidBody();
        m_Animation = new Animation();
        m_Animation->SetProps(m_TextureID, 1, 6, 80);
    }

    void Warrior::Draw()
    {
        m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

        SDL_Rect box = m_Collider->Get();
        SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);

    }

    void Warrior::Update(float dt) {
        m_Animation->SetProps("player", 1, 6, 100);
        m_RigidBody->UnsetForce();

        if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
            m_Animation->SetProps("player_run", 1, 10, 100);
            m_RigidBody->ApplyForceX(10);
        }

        if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
            m_Animation->SetProps("player_run", 1, 10, 100, SDL_FLIP_HORIZONTAL);
            m_RigidBody->ApplyForceX(-10);
        }

        m_RigidBody->Update(dt);
        m_Transform->TranslateX(m_RigidBody->Postition().X);

        // Giới hạn trong màn hình
        if (m_Transform->X < 0) {
            m_Transform->X = 0;
            m_RigidBody->SetPositionX(0); // Đồng bộ RigidBody
        }
        if (m_Transform->X + m_Width > SCREEN_WIDTH) {
            m_Transform->X = SCREEN_WIDTH - m_Width;
            m_RigidBody->SetPositionX(m_Transform->X); // Đồng bộ RigidBody
        }

        m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 84);
        m_Animation->Update();
    }

    void Warrior::Clean()
    {
        TextureManager::GetInstance()->Clean();
    }
