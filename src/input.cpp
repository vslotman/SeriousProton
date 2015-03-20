#include "input.h"
#include "engine.h"

P<WindowManager> InputHandler::windowManager;
bool InputHandler::touch_screen = false;
bool InputHandler::joystick = false;
int InputHandler::joystickHysteresis;
bool InputHandler::joystickMoved = false;
sf::Transform InputHandler::mouse_transform;

sf::Vector2f InputHandler::mousePos;
int InputHandler::mouse_wheel_delta;
sf::Vector2f InputHandler::joystickPosXY;
float InputHandler::joystick_xy_delta;
float InputHandler::joystickPosR;
float InputHandler::joystickPosZ;
int   InputHandler::joystickPosPovX;
int   InputHandler::joystickPosPovX_debounce;
int   InputHandler::joystickPosPovY;
int   InputHandler::joystickPosPovY_debounce;

bool InputHandler::mouse_button_down[sf::Mouse::ButtonCount];
bool InputHandler::keyboard_button_down[sf::Keyboard::KeyCount];
bool InputHandler::joystick_button_down[sf::Joystick::ButtonCount];
float InputHandler::joystick_axis_pos[sf::Joystick::AxisCount];
float InputHandler::axis_pos;

bool InputHandler::mouseButtonDown[sf::Mouse::ButtonCount];
bool InputHandler::mouseButtonPressed[sf::Mouse::ButtonCount];
bool InputHandler::mouseButtonReleased[sf::Mouse::ButtonCount];
bool InputHandler::keyboardButtonDown[sf::Keyboard::KeyCount];
bool InputHandler::keyboardButtonPressed[sf::Keyboard::KeyCount];
bool InputHandler::keyboardButtonReleased[sf::Keyboard::KeyCount];
bool InputHandler::joystickButtonDown[sf::Joystick::ButtonCount];
bool InputHandler::joystickButtonPressed[sf::Joystick::ButtonCount];
bool InputHandler::joystickButtonReleased[sf::Joystick::ButtonCount];
string InputHandler::keyboard_text_entry;

void InputHandler::initialize()
{
    memset(mouse_button_down, 0, sizeof(mouse_button_down));
    memset(keyboard_button_down, 0, sizeof(keyboard_button_down));
    memset(joystick_button_down, 0, sizeof(joystick_button_down));
    memset(joystick_axis_pos, 0, sizeof(joystick_axis_pos));
}

void InputHandler::update()
{
    if (!windowManager)
        windowManager = engine->getObject("windowManager");

    mousePos = sf::Vector2f(sf::Mouse::getPosition());
    mousePos = mousePos - sf::Vector2f(windowManager->window.getPosition());
    mousePos.x *= float(windowManager->virtualSize.x) / float(windowManager->window.getSize().x);
    mousePos.y *= float(windowManager->virtualSize.y) / float(windowManager->window.getSize().y);
    mousePos = mouse_transform.transformPoint(mousePos);
    for(unsigned int n=0; n<sf::Mouse::ButtonCount; n++)
    {
        bool down = mouse_button_down[n];
        mouseButtonPressed[n] = (!mouseButtonDown[n] && down);
        mouseButtonReleased[n] = (mouseButtonDown[n] && !down);
        mouseButtonDown[n] = down;
    }

    for(unsigned int n=0; n<sf::Keyboard::KeyCount; n++)
    {
        bool down = keyboard_button_down[n];
        keyboardButtonPressed[n] = (!keyboardButtonDown[n] && down);
        keyboardButtonReleased[n] = (keyboardButtonDown[n] && !down);
        keyboardButtonDown[n] = down;
    }

    if (touch_screen)
    {
        bool any_button_down = false;
        for(unsigned int n=0; n<sf::Mouse::ButtonCount; n++)
            if (mouseButtonDown[n] || mouseButtonReleased[n])
                any_button_down = true;
        if (!any_button_down)
        {
            mousePos.x = -1;
            mousePos.y = -1;
        }
    }

    if (joystick)
    {
        joystickMoved = false;
        axis_pos = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
        if (abs(axis_pos) > joystickHysteresis)
        {
            joystickPosXY.x = axis_pos;
            joystickMoved = true;
        }

        axis_pos = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
        if (abs(axis_pos) > joystickHysteresis)
        {
            joystickPosXY.y = axis_pos;
            joystickMoved = true;
        }

        axis_pos = sf::Joystick::getAxisPosition(0, sf::Joystick::R);
        if (abs(axis_pos) > joystickHysteresis)
        {
            joystickPosR = axis_pos;
            joystickMoved = true;
        }

        // Throttle-stick. This one doesn't need hysteresis
        axis_pos = sf::Joystick::getAxisPosition(0, sf::Joystick::Z);
        joystickPosZ = axis_pos;

        joystickPosPovX = (int) sf::Joystick::getAxisPosition(0, sf::Joystick::PovX);
        joystickPosPovY = (int) sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);


        for(unsigned int n=0; n<sf::Joystick::ButtonCount; n++)
        {
            bool down = joystick_button_down[n];
            joystickButtonPressed[n] = (!joystickButtonDown[n] && down);
            joystickButtonReleased[n] = (joystickButtonDown[n] && !down);
            joystickButtonDown[n] = down;
        }
    }
}

int InputHandler::getJoystickPosPovX()
{
    if (joystickPosPovX_debounce > 0)
        joystickPosPovX_debounce--;

    if (joystickPosPovX == 0)
        return joystickPosPovX;
    else if (joystickPosPovX_debounce == 0)
    {
        joystickPosPovX_debounce = 15;
        return joystickPosPovX;
    }
    else return 0;
}

int InputHandler::getJoystickPosPovY()
{
    if (joystickPosPovY_debounce > 0)
        joystickPosPovY_debounce--;

    if (joystickPosPovY == 0)
        return joystickPosPovY;
    else if (joystickPosPovY_debounce <= 0)
    {
        joystickPosPovY_debounce = 15;
        return joystickPosPovY;
    }
    else return 0;
}
