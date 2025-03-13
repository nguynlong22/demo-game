#include "GameOver.h"
#include "Engine.h"
#include "Play.h"

GameOver::GameOver(int finalScore) : m_FinalScore(finalScore)
{
    retryButton = {400, 200, 160, 80};
    exitButton = { 400, 400, 160, 80 };
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

    TextureManager::GetInstance()->DrawText("Game Over", 400, 100, 255, 255, 255);

    std::string scoreText = "Final Score: " + std::to_string(m_FinalScore);
    TextureManager::GetInstance()->DrawText(scoreText, 400, 150, 255, 255, 255);

    // Vẽ nút Play
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Xanh lá
    SDL_RenderFillRect(renderer, &retryButton);
    TextureManager::GetInstance()->DrawText("Retry", retryButton.x + 40, retryButton.y + 20, 255, 255, 255);

    // Vẽ nút Exit
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Đỏ
    SDL_RenderFillRect(renderer, &exitButton);
    TextureManager::GetInstance()->DrawText("Exit", exitButton.x + 40, exitButton.y + 20, 255, 255, 255);

    SDL_RenderPresent(renderer);
}

void GameOver::Enter()
{
    TextureManager::GetInstance()->LoadFont("assets/arial.ttf", 32);
}

void GameOver::Exit()
{

}
