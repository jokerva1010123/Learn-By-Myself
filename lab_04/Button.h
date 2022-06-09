#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <QPushButton>
#include <QDebug>

class Button : public QPushButton
{
    Q_OBJECT;

    enum buttonStatus
    {
        ACTIVE,
        NOT_ACTIVE
    };

public:
    explicit Button(QWidget *parent = nullptr);
    ~Button() override = default;

    void setFloor(const size_t floor);

signals:
    void pressSignal(bool, int);
    void unpressSignal();

public slots:
    void press();
    void unpress();

private:
    buttonStatus _status;
    size_t _curFloor;
};

#endif // BUTTON_H
