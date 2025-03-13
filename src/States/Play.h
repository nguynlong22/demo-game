#ifndef PLAY_H
#define PLAY_H

#include "GameState.h"
#include "Warrior.h"
#include "AppleThrower.h"
#include "Heart.h"

class PlayState : public GameState {
public:
    PlayState();
    ~PlayState() override;
    void Update(float dt) override;
    void Render() override;
    void Enter() override;
    void Exit() override;

    inline Warrior* GetPlayer() {return player;}
    void AddScore(int points);
    void LoseHeart(); // Thêm để giảm heart
    int GetScore() const { return score; }
    static bool HasPlayed() { return hasPlayed; }

private:
    static bool hasPlayed;
    FruitThrower* fruitThrower;
    Warrior* player;
    Heart* hearts; // Thêm Heart
    int score = 0;
};

#endif // PLAY_H
