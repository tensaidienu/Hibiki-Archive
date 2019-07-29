#include <algorithm>

#include "TextureManager.h"

#include "SDL2/SDL_image.h"

using namespace std;

TextureManager* TextureManager::textureManagerInstance = 0;

SDL_Surface* TextureManager::loadImgSurface(std::string fileName){
    return IMG_Load(fileName.c_str());
}

bool TextureManager::loadImg(std::string fileName, std::string id, SDL_Renderer* renderer, std::string transparency) {
    SDL_Surface* tempSurface = IMG_Load(fileName.c_str());
    if(tempSurface == 0) {
        return false;
    }

    if(transparency.compare("0")){        
        transparency.erase(std::remove(transparency.begin(), transparency.end(), '#'), transparency.end());
        while(transparency.length() != 6) {
            transparency += "0";
        }
        std::vector<string> color = SplitWithCharacters(transparency, 2);
        int r = stoi(color[0],nullptr,16);
        int g = stoi(color[1],nullptr,16);
        int b = stoi(color[2],nullptr,16);
        SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, r, g, b));
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

std::vector<std::string> TextureManager::SplitWithCharacters(const std::string& str, int splitLength) {
  int NumSubstrings = str.length() / splitLength;
  std::vector<std::string> ret;

  for (int i = 0; i < NumSubstrings; i++) {
     ret.push_back(str.substr(i * splitLength, splitLength));
  }

  // If there are leftover characters, create a shorter item at the end.
  if (str.length() % splitLength != 0) {
      ret.push_back(str.substr(splitLength * NumSubstrings));
  }


  return ret;
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

void TextureManager::drawRect(SDL_Renderer *renderer, SDL_Rect &rect) {
    SDL_RenderDrawRect(renderer, &rect);
    //SDL_RenderFillRect(renderer, &rect);
}

void TextureManager::clearFromTextureMap(std::string id) {
    textureMap.erase(id);
}

void TextureManager::clear() {
    textureMap.clear();
}