//
// Created by Oliver on 17.04.2024.
//

#include <stdexcept>
#include "InputHandler.h"

InputHandler::InputHandler() {

}

Vector2 InputHandler::WalkingDirection() {
    Vector2 direction = {0, 0};
    if (IsKeyDown(KEY_W)) {
        direction.y -= 1;
    }
    if (IsKeyDown(KEY_S)) {
        direction.y += 1;
    }
    if (IsKeyDown(KEY_A)) {
        direction.x -= 1;
    }
    if (IsKeyDown(KEY_D)) {
        direction.x += 1;
    }
    if (direction.x == 0 && direction.y == 0) {
        direction = {GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X), GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y)};
    }
    //in this implementation, keyboard is less accurate than gamepad
    return direction;
}
