#ifndef PIN_HPP
#define PIN_HPP

#include <QGraphicsItem>
#include <QPen>
#include <QPainter>
#include <iostream>
#include <QColor>
#include "state.hpp"

class Pin : public QGraphicsItem
{
public:
    Pin() { }

    Pin(QPen contour, qreal x, qreal y, qreal radius);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
    {
        QColor color;

        switch(m_state)
        {
        case State::LOGICAL_0:
            color = Qt::gray;
        case State::LOGICAL_1:
            color = Qt::green;
        case State::LOGICAL_Z:
            color = Qt::blue;
        case State::LOGICAL_X:
            color = Qt::red;
        default:
            color = Qt::darkRed;
        }

        m_contour.setColor(color);

        painter->setPen(m_contour);
        painter->drawEllipse(QRectF(m_posX, m_posY, m_radius, m_radius));
    }

    QRectF boundingRect() const override
    {
        return QRectF(m_posX, m_posY, m_radius, m_radius);
    }

private:
    QPen m_contour;
    State m_state;
    qreal m_posX, m_posY, m_radius;
};

#endif // PIN_HPP
