#ifndef AND_HPP
#define AND_HPP

#include "gate.hpp"
#include <QPainterPath>
#include <QPointF>
#include <QDebug>

class And : public AGate
{
public:
    And(QPen contour, const QVector<Pin*>& inputs, qreal x, qreal y, qreal length, qreal height) : AGate(contour, inputs, x, y, length, height)
    { printf("Create and gate"); }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
    {
        QPainterPath circlePath;
        QRectF boundingRect(m_posX, m_posY, m_length, m_height);
        QPointF center(m_posX + (m_length / 2), m_posY + (m_height / 2));
        QPointF end(m_posX + (m_length / 2), m_posY + m_height);
        circlePath.moveTo(end);
        circlePath.arcTo(boundingRect, 90, -180);
        painter->setPen(m_contour);
        painter->drawPath(circlePath);
        printf("paint And circuit\n");

        //qDebug() << "paint And circuit\n";
    }

    QRectF boundingRect() const override
    {
        return QRectF(0, 0, m_length, m_height);
    }
};

#endif // AND_HPP
