#ifndef CABIN_H
#define CABIN_H

#include <QObject>
#include <QTimer>

#include "defines.h"
#include "Door.h"

class Cabin : public QObject
{
    Q_OBJECT

    enum cabinStatus {
        WAITING,
        MOVING,
        FREE
    };

public:
    explicit Cabin(QObject *parent = nullptr);
    ~Cabin() override = default;

signals:
    void openDoor();
    void cabinFinished(bool, int=1);

public slots:
    void stopCabin();           // -> WAITS
    void moveCabin();           // -> MOVING
    void free();                // -> FREE

private:
    cabinStatus _status;
    Door _door;
    QTimer _moveTimer;
};

#endif // CABIN_H
