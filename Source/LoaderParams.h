#ifndef __LoaderParams_h__
#define __LoaderParams_h__

#include <iostream>
#include <string>

const std::string defaultType("Blocked");
const std::string defaultCallback("");

class LoaderParams {
    private:
        int x;
        int y;
        int width;
        int height;

        std::string textureID;
        std::string type;
        std::string callbackID;

        int numFrames;
        int animSpeed;
    public:
        LoaderParams(int x, int y, int width, int height, std::string textureID, 
                     std::string callbackID = defaultCallback, int numFrames = 0, int animSpeed = 0,
                     std::string type = defaultType) : 
                     x(x), y(y), width(width), height(height), textureID(textureID),
                     callbackID(callbackID), numFrames(numFrames), animSpeed(animSpeed), type(type) {}

        LoaderParams(std::string textureID, int x, int y, int width, int height,  
                    std::string type = defaultType) : x(x), y(y), width(width), height(height), 
                     textureID(textureID), type(type) {}

        int getX() const { return x; }
        int getY() const { return y; }
        int getWidth() const { return width; }
        int getHeight() const { return height; }
        std::string getTextureID() const { return textureID; }
        std::string getType() const { return type; }
        std::string getCallbackID() const { return callbackID; }
        int getNumFrames() const { return numFrames; }
        int getAnimSpeed() const { return animSpeed; }
};

#endif