#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"

class Warrior: public Character
{
    public:
        Warrior(Properties* props);

        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();

        SDL_Rect GetSwordHitbox();
    private:
        RigidBody* m_RigidBody;
        Animation* m_Animation;
};

#endif // WARRIOR_H
