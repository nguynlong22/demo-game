#ifndef WARRIOR_H
#define WARRIOR_H

#include "Engine.h"
#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Collider.h"
#include "TextureManager.h"
#include "Input.h"



class Warrior: public Character
{
    public:
        Warrior(Properties* props);

        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();

        SDL_Rect GetCollider() { return m_Collider->Get(); }
    private:
        RigidBody* m_RigidBody;
        Animation* m_Animation;
        Collider *m_Collider;
};

#endif // WARRIOR_H
