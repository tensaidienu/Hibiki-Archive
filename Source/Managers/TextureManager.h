#ifndef __TextureManager_h__
#define __TextureManager_h__

#include <iostream>
#include <map>
#include <vector>

#include "SDL2/SDL.h"

const std::string defaultString = std::string("0");

class TextureManager {
    private:
        TextureManager(){}
        ~TextureManager(){}

        static TextureManager* textureManagerInstance;

        std::map<std::string, SDL_Texture*> textureMap;        
    public:
        static TextureManager* getInstance() {
	        if(textureManagerInstance == 0){
		        textureManagerInstance = new TextureManager();
		        return textureManagerInstance;
	        }
	        return textureManagerInstance;
        }
        SDL_Surface* loadImgSurface(std::string fileName);
        bool loadImg(std::string fileName, std::string id, SDL_Renderer* renderer, std::string transparency = defaultString);
        std::vector<std::string> SplitWithCharacters(const std::string& str, int splitLength);
        void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void drawRect(SDL_Renderer *renderer, SDL_Rect &rect);
        void clearFromTextureMap(std::string id);
        void clear();
};

typedef	TextureManager TheTextureManager;

#endif