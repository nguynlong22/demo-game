#include "Menu.h"

using namespace std;

Menu::Menu(){}

bool Menu::Init()
{
    m_Ctxt = Engine::GetInstance()->GetRenderer();
    cout << "Menu \n";
    return true;
}

bool Menu::Exit()
{
    cout << "exit \n";
    return true;
}

void Menu::Update()
{

}

void Menu::Render()
{
    SDL_SetRenderDrawColor(m_Ctxt, 16, 45, 70, 255);
    SDL_RenderClear();

    SDL_RenderPresent(m_Ctxt);
}

void Menu::StartGame()
{
    cout << "Start \n";
}

void Menu::Settings()
{
    cout << "Settings \n";
}

void Menu::Editor()
{
    cout << "Editor \n";
}

void Menu::Quit()
{
    cout << "Quit \n";
}

