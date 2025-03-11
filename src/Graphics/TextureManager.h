#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include<string>
#include "SDL.h"
#include "SDL_ttf.h"
#include<map>

using namespace std;

class TextureManager
{
    public:
        static TextureManager* GetInstance() {
            return s_Instance = (s_Instance != nullptr)? s_Instance : new TextureManager();
        }

        bool Load(string id, string filename);
        void Drop(string id);
        void Clean();

        void Draw(string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawFrame(string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void LoadFont(const std::string& fontPath, int fontSize);
        void DrawText(const std::string& text, int x, int y, Uint8 r, Uint8 g, Uint8 b);

        //map<string, SDL_Texture*> m_TextureMap;
    private:
        TextureManager() : m_Font(nullptr) {}
        static TextureManager* s_Instance;
        map<std::string, SDL_Texture*> m_TextureMap;
        TTF_Font* m_Font;
};

#endif // TEXTUREMANAGER_H
