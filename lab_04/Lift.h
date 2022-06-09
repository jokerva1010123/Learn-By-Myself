#ifndef LIFT_H
#define LIFT_H

#include <QObject>

#include "Cabin.h"
#include "Controller.h"

class Lift : public QObject
{
    Q_OBJECT

public:
    explicit Lift(QObject *parent = nullptr);
    ~Lift() = default;

    QWidget* widget();

private:
    Controller _controller;
    Cabin _cabin;
};


#endif // LIFT_H
