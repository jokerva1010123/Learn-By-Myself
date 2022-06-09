#include "Door.h"
#include "defines.h"

Door::Door() :_status(CLOSED)
{
    qDebug() << "DOOR CLOSED!";

    QObject::connect(&_openTimer, SIGNAL(timeout()), this, SLOT(wasOpened())); // timeout() - signal from qtimer
    QObject::connect(&_waitTimer,  SIGNAL(timeout()), this, SLOT(beginClosing()));
    QObject::connect(&_closeTimer, SIGNAL(timeout()), this, SLOT(wasClosed()));
}

void Door::beginOpening()
{
    if (_status == CLOSED || _status == CLOSING)
    {

        doorStatus temp = _status;
        this->_status = OPENING;
        if (temp == CLOSED)
        {
            this->_openTimer.start(DOOR_TIME);
        }
        else
        {
            auto delta_timer = this->_closeTimer.remainingTime();
            _closeTimer.stop();
            this->_closeTimer.start(DOOR_TIME - delta_timer);
        }

        qDebug() << "DOOR OPENING ...";
    }
}


void Door::wasOpened()
{
    if (_status == OPENING)
    {
        _status = OPENED;
        qDebug() << "DOOR OPENED!";

        this->_waitTimer.start(WAIT_TIME);
    }
}

void Door::beginClosing()
{
    if (_status == OPENED)
    {
        _status = CLOSING;
        qDebug() << "DOOR CLOSING ...";

        _closeTimer.start(DOOR_TIME);
    }
}

void Door::wasClosed()
{
    if (_status == CLOSING)
    {
        _status = CLOSED;
        qDebug() << "DOOR CLOSED!";

        emit doorClosed();
    }
}
