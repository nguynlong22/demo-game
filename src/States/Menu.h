#ifndef MENU_H
#define MENU_H
#include "GameState.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Input.h"

class Menu : public GameState {
public:
    Menu();
    ~Menu() override {}
    void Update(float dt) override;
    void Render() override;
    void Enter() override;
    void Exit() override;

private:
    SDL_Rect playButton;
    SDL_Rect exitButton;
    SDL_Rect continueButton;
};

#endif // MENU_H
