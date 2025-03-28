#ifndef PLAY_H
#define PLAY_H

#include "GameState.h"
#include "Warrior.h"
#include "AppleThrower.h"
#include "Heart.h"
#include "SDL_mixer.h"

class PlayState : public GameState {
public:
    PlayState();
    ~PlayState() override;
    void Update(float dt) override;
    void Render() override;
    void Enter() override;

    inline Warrior* GetPlayer() {return player1;}
    inline Warrior* GetPlayer2() {return player2;}
    void AddScorePlayer1(int points);
    void AddScorePlayer2(int points);
    void LoseHeartPlayer1(); // Giảm mạng Player 1
    void LoseHeartPlayer2(); // Giảm mạng Player 2
    int GetScorePlayer1() const { return score1; } // Lấy điểm Player 1
    int GetScorePlayer2() const { return score2; } // Lấy điểm Player 2
    Heart* GetHeartsPlayer1() const { return hearts1; } // Truy cập hearts Player 1
    Heart* GetHeartsPlayer2() const { return hearts2; } // Truy cập hearts Player 2
    static bool HasPlayed() { return hasPlayed; }
    int GetActiveSide() const { return activeSide; } // 0: cả hai, 1: chỉ Player 1, 2: chỉ Player 2

private:
    static bool hasPlayed;
    Mix_Chunk* pickupSound = nullptr;
    FruitThrower* fruitThrower;
    Warrior* player1;
    Warrior* player2;
    Heart* hearts1;
    Heart* hearts2;
    int score1 = 0, score2 = 0;
    int activeSide = 0;
};

#endif // PLAY_H
