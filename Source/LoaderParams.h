#ifndef __LoaderParams_h__
#define __LoaderParams_h__

#include <iostream>
#include <string>

class LoaderParams {
    private:
        int x;
        int y;
        int width;
        int height;

        std::string textureID;

        int numFrames;
        int callbackID;
        int animSpeed;
    public:
        LoaderParams(int x, int y, int width, int height, std::string textureID, int numFrames = 0, 
                     int callbackID = 0, int animSpeed = 0) : x(x), y(y), width(width), height(height), 
                     textureID(textureID), numFrames(numFrames), callbackID(callbackID), animSpeed(animSpeed) {}
        int getX() const { return x; }
        int getY() const { return y; }
        int getWidth() const { return width; }
        int getHeight() const { return height; }
        std::string getTextureID() const { return textureID; }
        int getNumFrames() const { return numFrames; }
        int getCallbackID() const { return callbackID; }
        int getAnimSpeed() const { return animSpeed; }
};

#endif