#ifndef INPUT_H
#define INPUT_H

#include "windowManager.h"
#include "stringImproved.h"
#include "Updatable.h"

class InputHandler
{
    static P<WindowManager> windowManager;

    static sf::Vector2f mousePos;
    static int mouse_wheel_delta;
    static bool mouseButtonDown[sf::Mouse::ButtonCount];
    static bool mouseButtonPressed[sf::Mouse::ButtonCount];
    static bool mouseButtonReleased[sf::Mouse::ButtonCount];
    static bool mouse_button_down[sf::Mouse::ButtonCount];

    static bool keyboardButtonDown[sf::Keyboard::KeyCount];
    static bool keyboardButtonPressed[sf::Keyboard::KeyCount];
    static bool keyboardButtonReleased[sf::Keyboard::KeyCount];
    static bool keyboard_button_down[sf::Keyboard::KeyCount];
    static string keyboard_text_entry;

    static float joystick_axis_pos[sf::Joystick::AxisCount];

    static sf::Vector2f joystickPosXY;
    static float axis_pos;
    static float joystick_xy_delta;
    static bool joystickButtonDown[sf::Joystick::ButtonCount];
    static bool joystickButtonPressed[sf::Joystick::ButtonCount];
    static bool joystickButtonReleased[sf::Joystick::ButtonCount];
    //TODO: Add an axis-specifier
    static bool joystickMoved;
    static bool joystick_button_down[sf::Joystick::ButtonCount];


    static void initialize();
public:
    static bool touch_screen;
    static bool joystick;
    static int  joystickHysteresis;
    static sf::Transform mouse_transform;

    static void update();

    static bool keyboardIsDown(sf::Keyboard::Key key) { return keyboardButtonDown[key]; }
    static bool keyboardIsPressed(sf::Keyboard::Key key) { return keyboardButtonPressed[key]; }
    static bool keyboardIsReleased(sf::Keyboard::Key key) { return keyboardButtonReleased[key]; }
    static string getKeyboardTextEntry() { return keyboard_text_entry; }

    static sf::Vector2f getMousePos() { return mousePos; }
    static bool mouseIsDown(sf::Mouse::Button button) { return mouseButtonDown[button]; }
    static bool mouseIsPressed(sf::Mouse::Button button) { return mouseButtonPressed[button]; }
    static bool mouseIsReleased(sf::Mouse::Button button) { return mouseButtonReleased[button]; }
    static int getMouseWheelDelta() { return mouse_wheel_delta; }

    static sf::Vector2f getJoystickPosXY() { return joystickPosXY; }
    static bool joystickIsDown(unsigned int button) { return joystickButtonDown[button]; }
    static bool joystickIsPressed(unsigned int button) { return joystickButtonPressed[button]; }
    static bool joystickIsReleased(unsigned int button) { return joystickButtonReleased[button]; }
    static bool joystickHasMoved() { return joystickMoved; }
    static float getJoystickXYDelta() { return joystick_xy_delta; }

    friend class Engine;
};


#endif//INPUT_H
