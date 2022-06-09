#include "Controller.h"

#include <QDebug>

Controller::Controller(QWidget *parent) : QWidget(parent)
{
    this->_layout = std::unique_ptr<QVBoxLayout>(new QVBoxLayout);
    this->setLayout(this->_layout.get());

    for (size_t i = 0; i < FLOOR_MAX; i++)
    {
        auto new_button = std::make_shared<Button>();
        new_button->setFloor(FLOOR_MAX - i);
        new_button->setText(QString::number(FLOOR_MAX - i));

        this->_buttons.insert(this->_buttons.begin(), new_button);
        _layout->addWidget(dynamic_cast<QPushButton *>(new_button.get()));

        _floorsToVisit.push_back(false);

        //button pressed => add floor to target
        QObject::connect(new_button.get(), SIGNAL(pressSignal(bool,int)), this, SLOT(newTarget(bool,int)));
    }

    QObject::connect(this, SIGNAL(reachFloorSignal()), this, SLOT(reachFloor()));
}

void Controller::newTarget(bool got_new, int floor)
{
    this->_status = BUSY;

    if (got_new)
    {
        this->_floorsToVisit[floor - 1] = true;

        _identifyNewTarget(floor);
        _targetFloor = floor;
        _decideDirection();

        if (_direction == STAY)
        {
            emit reachFloorSignal();
        }
        else
        {
            emit moveCabinSignal();
        }
    }
    else if (_identifyNewTarget(floor))
    {
        _targetFloor = floor;
        _decideDirection();

        if (_direction != STAY)
        {
             _updateFloor();
            emit moveCabinSignal();
        }
        else
        {
            emit reachFloorSignal();
        }
     }
}

void Controller::_decideDirection()
{
    if (_targetFloor > _curFloor)
    {
        _direction = UP;
    }
    else if (_targetFloor < _curFloor)
    {
        _direction = DOWN;
    }
    else
    {
        _direction = STAY;
    }
}

bool Controller::_identifyNewTarget(int &new_target)
{
    bool founded = false;

    Direction dir;

    if (_direction != STAY)
    {
        dir = _direction;
    }
    else
    {
        dir = DOWN;
    }

    for (int i = _curFloor; !founded && i <= FLOOR_MAX && i > 0; i = i + dir)
    {
        if (_floorsToVisit[i - 1])
        {
            new_target = i;
            founded = true;
        }
    }

    if (!founded)
    {
        dir = ((dir == UP) ? DOWN : UP);

        for (int i = _curFloor; !founded && i <= FLOOR_MAX && i > 0; i = i + dir)
        {
            if (_floorsToVisit[i - 1])
            {
                new_target = i;
                founded = true;
            }
        }
    }

    return founded;
}

void Controller::reachFloor()
{
    if (_status == BUSY)
    {

         _status = FREE;

        qDebug() << "[!] The elevator REACHES the floor " << _targetFloor << "th";

        emit _buttons[_targetFloor - 1]->unpressSignal();   // the button is released
        _floorsToVisit[_targetFloor - 1] = false;           // no need to visit

        _identifyNewTarget(_targetFloor);
        emit stopCabinSignal();
    }
}

void Controller::_updateFloor()
{
    _curFloor += _direction;

     qDebug() << "... The elevator goes to the floor" << _curFloor << "th";
}
