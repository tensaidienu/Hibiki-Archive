#include "TextureManager.h"

#include "SDL2/SDL_image.h"

using namespace std;

TextureManager* TextureManager::textureManagerInstance = 0;

SDL_Surface* TextureManager::loadImgSurface(std::string fileName){
    return IMG_Load(fileName.c_str());
}

bool TextureManager::loadImg(std::string fileName, std::string id, SDL_Renderer* renderer, int transparency) {
    SDL_Surface* tempSurface = IMG_Load(fileName.c_str());
    if(tempSurface == 0) {
        return false;
    }

    if(transparency > 0){
        int r = ((transparency >> 16) & 0xFF) / 255.0;  // Extract the RR byte
        int g = ((transparency >> 8) & 0xFF) / 255.0;   // Extract the GG byte
        int b = ((transparency) & 0xFF) / 255.0;
        SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 248, 0, 248));
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    // everything went ok, add the texture to our list
    if(texture != 0) {
        textureMap[id] = texture;
        return true;
    }
    // reaching here means something went wrong
    return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* renderer, SDL_RendererFlip flip) {
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    std::cout << "TextureManager::draw: " << id << "\n";

    SDL_RenderCopyEx(renderer, textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *renderer, SDL_RendererFlip flip) {
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = width * currentFrame;
    srcRect.y = height * (currentRow - 1);
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(renderer, textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *renderer, SDL_RendererFlip flip) {
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = margin + (spacing + width) * currentFrame;
    srcRect.y = margin + (spacing + height) * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopyEx(renderer, textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::clearFromTextureMap(std::string id) {
    textureMap.erase(id);
}