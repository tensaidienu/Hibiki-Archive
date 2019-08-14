#ifndef __InputManager_h__
#define __InputManager_h__

#include <vector>

#include "SDL2/SDL.h"

#include "../Vector2D.h"

enum MouseButtons {
    LEFT  = 0,
    MIDDLE = 1,
    RIGHT = 2
};

const int joystickDeadZone = 1000;

class InputManager {
    private:
        InputManager();
        ~InputManager();

        static InputManager* InputManagerInstance;

        std::vector<SDL_Joystick*> joysticks;
        std::vector<std::pair<Vector2D*, Vector2D*> > joysticksValues;
        std::vector<std::vector<bool> > buttonStates;
        bool joysticksInitialised = false;

        std::vector<bool> mouseButtonStates;
        Vector2D* mousePosition;

        Uint8* keyStates;

        // handle keyboard events
        void onKeyDown();
        void onKeyUp();
        // handle mouse events
        void onMouseMove(SDL_Event& event);
        void onMouseButtonDown(SDL_Event& event);
        void onMouseButtonUp(SDL_Event& event);
        // handle joysticks events
        void onJoystickAxisMove(SDL_Event& event);
        void onJoystickButtonDown(SDL_Event& event);
        void onJoystickButtonUp(SDL_Event& event);
    public:
        static InputManager* getInstance() {
            if(InputManagerInstance == 0) {
                InputManagerInstance = new InputManager();
            }
            return InputManagerInstance;
        }
        void initialiseJoysticks();
        int xvalue(int joy, int stick);
        int yvalue(int joy, int stick);
        void update();
        void clear();        
        bool isJoysticksInitialised() {
            return joysticksInitialised;
        }
        bool isKeyDown(SDL_Scancode key);
        bool getButtonState(int joystick, int buttonNumber);
        bool getMouseButtonState(int buttonNumber);
        Vector2D* getMousePosition();
        void reset();
};

typedef InputManager TheInputManager;

#endif