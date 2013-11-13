#include "playerinput.h"

PlayerInput::PlayerInput() :
    m_throttle(false),
    m_brakes(false),
    m_turnLeft(false),
    m_turnRight(false)
{
}

bool PlayerInput::brakes() const
{
    return m_brakes;
}

void PlayerInput::setBrakes(bool enabled)
{
    m_brakes = enabled;
}

bool PlayerInput::throttle() const
{
    return m_throttle;
}

void PlayerInput::setThrottle(bool enabled)
{
    m_throttle = enabled;
}

bool PlayerInput::turnLeft() const
{
    return m_turnLeft;
}

void PlayerInput::setTurnLeft(bool enabled)
{
    m_turnLeft = enabled;
}

bool PlayerInput::turnRight() const
{
    return m_turnRight;
}

void PlayerInput::setTurnRight(bool enabled)
{
    m_turnRight = enabled;
}
