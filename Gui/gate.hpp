#ifndef GATE_H
#define GATE_H

#include <QGraphicsItem>
#include <QObject>
#include <QRectF>
#include <QPainter>
#include <QPen>
#include "pin.hpp"
#include <QVector>
#include <QGraphicsSceneMouseEvent>
#include "gui.h"

//template<typename T>
//using Inputs = QVector<Pin>;

//using Output = Pin;

class GUI_EXPORT AGate : public QGraphicsItem
{
public:
    AGate(size_t id, QPen contour, const QVector<Pin*>& inputs, qreal posX, qreal posY, qreal length, qreal height) :
        m_id(id),
        m_posX(posX),
        m_posY(posY),
        m_inputs(inputs),
        m_contour(contour),
        m_length(height),
        m_height(length)
    {

    }

    size_t m_id;
    QPen m_contour;
    QVector<Pin*> m_inputs;
    qreal m_posX, m_posY, m_length, m_height;
};

#endif // GATE_H
