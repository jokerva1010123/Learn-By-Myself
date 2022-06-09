#include "Button.h"

Button::Button(QWidget *parent) : QPushButton(parent)
{
    _status = NOT_ACTIVE;
    _curFloor = 1;

    QObject::connect(this, SIGNAL(clicked()), this, SLOT(press()));
    QObject::connect(this, SIGNAL(unpressSignal()), this, SLOT(unpress()));
}

void Button::setFloor(const size_t floor)
{
    _curFloor = floor;
}

void Button::press()
{
    if (this->_status == NOT_ACTIVE)
    {
        this->_status = ACTIVE;

        this->setStyleSheet("background-color:red");
        this->update();

        qDebug() << "CALL FROM" << this->_curFloor << "th FLOOR!";

        this->setDisabled(true);

        emit pressSignal(true, this->_curFloor);
    }
}

void Button::unpress()
{
    if (this->_status == ACTIVE)
    {
        this->_status = NOT_ACTIVE;

        this->setStyleSheet("background-color:lightblue");
        this->update();

        this->setDisabled(false);
    }
}
