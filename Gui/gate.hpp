#ifndef GATE_H
#define GATE_H

#include <QGraphicsItem>
#include <QObject>
#include <QRectF>
#include <QPainter>
#include <QPen>
#include "pin.hpp"
#include <QVector>

//template<typename T>
//using Inputs = QVector<Pin>;

//using Output = Pin;

class AGate : public QGraphicsItem
{
public:
    AGate(QPen contour, const QVector<Pin*>& inputs, qreal posX, qreal posY, qreal length, qreal height) :
        m_posX(posX),
        m_posY(posY),
        m_inputs(inputs),
        m_contour(contour),
        m_length(height),
        m_height(length)
    {

    }

protected:
    QPen m_contour;
    QVector<Pin*> m_inputs;
    qreal m_posX, m_posY, m_length, m_height;
};

#endif // GATE_H
