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
        //m_CurrentState = "run";
    }

    void Warrior::Draw()
    {
        m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

        SDL_Rect box = m_Collider->Get();
        SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);

        //SDL_Rect swordBox = GetSwordHitbox();
        //if (swordBox.w > 0 && swordBox.h > 0) {
        //    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 255, 255, 0, 255); // Vàng cho sword hitbox
        //    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &swordBox);
        //}

        //SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255); // Reset
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

        //if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)) {
          //  m_Animation->SetProps("player_attack3", 1, 6, 45);
            //m_CurrentState = "attack3";
        //}

        m_RigidBody->Update(dt);
        m_Transform->TranslateX(m_RigidBody->Postition().X);
        m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 84);
        m_Animation->Update();
    }

    /*SDL_Rect Warrior::GetSwordHitbox() {
        int swordWidth, swordHeight, offsetX, offsetY;

        if (m_CurrentState == "attack1") {
            // Cú chém ngang cơ bản
            swordWidth = 60;   // Rộng vừa phải
            swordHeight = 20;  // Cao vừa đủ
            offsetX = GetWidth(); // Bắt đầu từ cạnh phải của Warrior (96)
            offsetY = 80;      // Dịch xuống dưới so với Y của Warrior
        }
        else if (m_CurrentState == "attack2") {
            // Cú chém cao hoặc đâm
            swordWidth = 60;   // Hẹp hơn
            swordHeight = 20;  // Cao hơn
            offsetX = GetWidth() + 10; // Dịch xa hơn một chút về phải
            offsetY = 120;     // Dịch lên trên để khớp với cú vung cao
        }
        else if (m_CurrentState == "attack3") {
            // Cú chém mạnh, rộng
            swordWidth = 80;   // Rộng hơn
            swordHeight = 15;  // Mỏng hơn
            offsetX = GetWidth() + 20; // Dịch xa hơn về phải
            offsetY = 30;      // Dịch xuống dưới để khớp với cú chém lớn
        }
        else { // "run" hoặc trạng thái khác
            swordWidth = 0;    // Không có hitbox
            swordHeight = 0;
            offsetX = 0;
            offsetY = 0;
        }

        return { (int)GetX() + offsetX, (int)GetY() + offsetY, swordWidth, swordHeight };
    }*/

    void Warrior::Clean()
    {
        TextureManager::GetInstance()->Clean();
    }
