#ifndef GAMEOVER_H
#define GAMEOVER_H
#include "GameState.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Input.h"


class GameOver : public GameState
{
public:
    GameOver(int score1, int score2, int winner);
    void Update(float dt) override;
    void Render() override;
    void Enter() override;
    void Exit() override;

private:
    SDL_Rect retryButton;
    SDL_Rect exitButton;
    int m_Score1;
    int m_Score2;
    int m_Winner;
};

#endif // GAMEOVER_H
