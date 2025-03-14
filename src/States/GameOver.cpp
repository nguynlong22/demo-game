#include "GameOver.h"
#include "Engine.h"
#include "Play.h"

GameOver::GameOver(int score1, int score2, int winner)
    : m_Score1(score1), m_Score2(score2), m_Winner(winner)
{
    retryButton = {430, 470, 160, 80};
    exitButton = { 430, 570, 160, 80 };
}

void GameOver::Update(float dt)
{
    if (Input::GetInstance()->GetMouseButtonDown(1)) { // Nhấn chuột trái
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        if (mouseX >= retryButton.x && mouseX <= retryButton.x + retryButton.w &&
            mouseY >= retryButton.y && mouseY <= retryButton.y + retryButton.h) {
            Engine::GetInstance()->PushState(new PlayState());
        }
        if (mouseX >= exitButton.x && mouseX <= exitButton.x + exitButton.w &&
            mouseY >= exitButton.y && mouseY <= exitButton.y + exitButton.h) {
            Engine::GetInstance()->Quit();
        }
    }
}

void GameOver::Render()
{
    SDL_Renderer* renderer = Engine::GetInstance()->GetRenderer();
    SDL_RenderClear(renderer);
    TextureManager::GetInstance()->Draw("bg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    std::string winnerText = (m_Winner == 1) ? "Player 1 Wins!" : "Player 2 Wins!";
    TextureManager::GetInstance()->DrawText(winnerText, 400, 250, 255, 255, 0); // Màu vàng

    std::string scoreText1 = "P1 Final Score: " + std::to_string(m_Score1);
    TextureManager::GetInstance()->DrawText(scoreText1, 400, 300, 255, 255, 255);

    std::string scoreText2 = "P2 Final Score: " + std::to_string(m_Score2);
    TextureManager::GetInstance()->DrawText(scoreText2, 400, 350, 255, 255, 255);

    // Vẽ nút Play
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
    SDL_RenderFillRect(renderer, &retryButton);
    TextureManager::GetInstance()->DrawText("Retry", retryButton.x + 40, retryButton.y + 20, 255, 255, 255);

    // Vẽ nút Exit
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
    SDL_RenderFillRect(renderer, &exitButton);
    TextureManager::GetInstance()->DrawText("Exit", exitButton.x + 40, exitButton.y + 20, 255, 255, 255);

    SDL_RenderPresent(renderer);
}

void GameOver::Enter()
{
    TextureManager::GetInstance()->LoadFont("assets/BubblegumSans.ttf", 32);
}

void GameOver::Exit()
{

}
