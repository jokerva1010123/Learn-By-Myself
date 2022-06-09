#include "Cabin.h"

#include <QDebug>

Cabin::Cabin(QObject *parent) : QObject(parent)
{
    _status = FREE;

    QObject::connect(this, SIGNAL(openDoor()), &_door, SLOT(beginOpening()));

    QObject::connect(&_moveTimer, SIGNAL(timeout()), this, SLOT(free()));

    QObject::connect(&_door, SIGNAL(doorClosed()), this, SLOT(free()));
}

void Cabin::stopCabin()
{
        _status = WAITING;

        _moveTimer.stop();
        emit openDoor(); //  open the door
 }

void Cabin::moveCabin()
{
    if (_status == FREE)
    {
        _status = MOVING;
        _moveTimer.start(MOVE_TIME);
    }
}

void Cabin::free()
{
    if (_status != FREE)
    {
        _status = FREE;
        emit cabinFinished(false);
    }
}

