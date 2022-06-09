#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QDebug>
#include <vector>
#include <memory>

#include "defines.h"
#include "Button.h"


class Controller : public QWidget
{
    Q_OBJECT

    enum controllerStatus
    {
        FREE,
        BUSY
    };

public:
    explicit Controller(QWidget *parent = nullptr);
    ~Controller() override = default;

signals:
    void stopCabinSignal();
    void moveCabinSignal();
    void reachFloorSignal();

public slots:
    void newTarget(bool ,int = 1);              // -> BUSY
    void reachFloor();                          // -> FREE

private:
    bool _identifyNewTarget(int &new_target);
    void _decideDirection();
    void _updateFloor();

private:
    int _curFloor = 1;
    int _targetFloor = 1;

    Direction _direction = STAY;

    controllerStatus _status = FREE;
    std::vector<bool> _floorsToVisit;

    std::vector<std::shared_ptr<Button>> _buttons;
    std::unique_ptr<QVBoxLayout> _layout;

};

#endif // CONTROLLER_H
