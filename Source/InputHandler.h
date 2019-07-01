#ifndef __InputHandler_h__
#define __InputHandler_h__

#include <vector>

#include "SDL2/SDL.h"

#include "Vector2D.h"

enum MouseButtons {
    LEFT  = 0,
    MIDDLE = 1,
    RIGHT = 2
};

const int joystickDeadZone = 1000;

class InputHandler {
    private:
        InputHandler();
        ~InputHandler() {}

        static InputHandler* InputHandlerInstance;

        std::vector<SDL_Joystick*> joysticks;
        std::vector<std::pair<Vector2D*, Vector2D*>> joysticksValues;
        std::vector<std::vector<bool>> buttonStates;
        bool joysticksInitialised;

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
        static InputHandler* getInstance() {
            if(InputHandlerInstance == 0) {
                InputHandlerInstance = new InputHandler();
            }
            return InputHandlerInstance;
        }
        void initialiseJoysticks();
        int xvalue(int joy, int stick);
        int yvalue(int joy, int stick);
        void update();
        void clean();        
        bool isJoysticksInitialised() {
            return joysticksInitialised;
        }
        bool isKeyDown(SDL_Scancode key);
        bool getButtonState(int joystick, int buttonNumber);
        bool getMouseButtonState(int buttonNumber);
        Vector2D* getMousePosition();
        void reset();
};

typedef InputHandler TheInputHandler;

#endif