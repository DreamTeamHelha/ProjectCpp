#pragma once

///
/// Classe encapsulant la gestion des contrôle de jeu.
///
class PlayerInput
{
public:

    PlayerInput();

    bool throttle() const;
    void setThrottle(bool enabled);

    bool brakes() const;
    void setBrakes(bool enabled);

    bool turnLeft() const;
    void setTurnLeft(bool enabled);

    bool turnRight() const;
    void setTurnRight(bool enabled);

private:

    bool m_throttle;
    bool m_brakes;
    bool m_turnLeft;
    bool m_turnRight;
};
