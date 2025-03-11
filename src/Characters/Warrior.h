#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Collider.h"

class Warrior: public Character
{
    public:
        Warrior(Properties* props);

        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();

        //SDL_Rect GetSwordHitbox();
        SDL_Rect GetCollider() { return m_Collider->Get(); }
    private:
        RigidBody* m_RigidBody;
        Animation* m_Animation;

        Collider *m_Collider;
        //std::string m_CurrentState;
};

#endif // WARRIOR_H
