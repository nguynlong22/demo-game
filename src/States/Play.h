#ifndef PLAY_H
#define PLAY_H

#include "GameState.h"
#include "Warrior.h"
#include "AppleThrower.h"

class PlayState : public GameState {
public:
    PlayState();
    ~PlayState() override;
    void Update(float dt) override;
    void Render() override;
    void Enter() override;
    void Exit() override;

    inline Warrior* GetPlayer() {return player;}

private:
    AppleThrower* appleThrower;
    Warrior* player;
};

#endif // PLAY_H
