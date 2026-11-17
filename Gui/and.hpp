#ifndef AND_HPP
#define AND_HPP

#include "gate.hpp"
#include <QPainterPath>
#include <QPointF>
#include <QDebug>

class GUI_EXPORT And : public AGate
{
public:
    And(size_t id, QPen contour, const QVector<Pin*>& inputs, qreal x, qreal y, qreal length, qreal height) :
        AGate(id, contour, inputs, x, y, length, height)
    {
        //setFlag(QGraphicsItem::ItemIsMovable, true);
        setFlag(QGraphicsItem::ItemIsSelectable, true);

        setPos(m_posX, m_posY);

        printf("Create and gate");
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
    {
        QPainterPath circlePath;
        QRectF bbox(0, 0, m_length, m_height);
        QPointF center(m_length / 2, m_height / 2);
        QPointF end(m_length / 2, m_height);
        circlePath.moveTo(end);
        circlePath.arcTo(bbox, 90, -180);

        if (isActive)
        {
            m_contour.setColor(Qt::green);
        }

        painter->setPen(m_contour);

        painter->drawPath(circlePath);
        //printf("paint And circuit\n");

        //qDebug() << "paint And circuit\n";

        painter->drawRect(this->boundingRect());
    }

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override
    {
        isActive = true;
        this->update();
        printf("And gate pressed\n");
    }

    QRectF boundingRect() const override
    {
        return QRectF(0, 0, m_length, m_height);
    }

    bool isActive = false;
};

#endif // AND_HPP
