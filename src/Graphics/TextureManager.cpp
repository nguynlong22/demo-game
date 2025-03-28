#include "TextureManager.h"

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::Load(string id, string filename)
{
    if (m_TextureMap.find(id) != m_TextureMap.end()) {
        return true;
    }

    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == nullptr) {
        SDL_Log("Failed to load texture: %s, %s", filename.c_str(), SDL_GetError());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);

    if (texture == nullptr) {
        SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        return false;
    }

    m_TextureMap[id] = texture;
    return true;
}


void TextureManager::Draw(string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {0, 0, width, height};
    SDL_Rect dstRect = {x, y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(string id, int x, int y, int width, int height,int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {width*frame, height*(row-1), width, height};
    SDL_Rect dstRect = {x, y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::LoadFont(const std::string& fontPath, int fontSize) {
    m_Font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!m_Font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
    }
}

void TextureManager::DrawText(const std::string& text, int x, int y, Uint8 r, Uint8 g, Uint8 b) {
    if (!m_Font) return;
    SDL_Color color = { r, g, b, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(m_Font, text.c_str(), color);
    if (!surface) {
        SDL_Log("Failed to render text: %s", TTF_GetError());
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    SDL_Rect dst = { x, y, w, h };
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), texture, nullptr, &dst);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void TextureManager::Drop(string id)
{
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}

void TextureManager::Clean()
{
    for (auto& pair : m_TextureMap) {
        SDL_DestroyTexture(pair.second);
    }
    m_TextureMap.clear();
    if (m_Font) {
        TTF_CloseFont(m_Font);
        m_Font = nullptr;
    }
}

