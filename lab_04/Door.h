#ifndef DOOR_H
#define DOOR_H

#include <QObject>
#include <QDebug>
#include <QTimer>

class Door : public QObject
{
    Q_OBJECT

    enum doorStatus
    {
        OPENED,
        CLOSED,
        OPENING,
        CLOSING
    };

public:
    Door();
    ~Door() override = default;

signals:
    void doorClosed();

private slots:
    void beginClosing();        // ->Closing...
    void beginOpening();        // ->Opening...

    void wasClosed();           // ->Closed
    void wasOpened();           // ->Opened

private:
    doorStatus _status;

    QTimer _openTimer;
    QTimer _closeTimer;
    QTimer _waitTimer;
};

#endif // DOOR_H
