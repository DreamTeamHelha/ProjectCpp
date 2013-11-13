#include "car.h"
#include "mathutils.h"
#include <cmath>
#include <iostream>
#include "vector.h"
#include "rotation.h"

Car::Car(QGraphicsItem *graphicsItem, b2Body *physicsBody) :
    Object(graphicsItem, physicsBody)
{
}

void Car::step(qreal throttle, qreal brakes, qreal steering)
{
    if (physicsBody())
    {
        float accel = 0;

        if (throttle > 0)
            accel += 200000;
        if (brakes > 0)
           accel -= 100000;

        Vector vAccel = (Vector)(Rotation::radians(physicsBody()->GetAngle()));
        vAccel *= accel;

        physicsBody()->ApplyForceToCenter(vAccel);

        if (steering != 0)
            physicsBody()->ApplyTorque(steering*200000);
    }
}
