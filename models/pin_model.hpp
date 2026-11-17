#ifndef PIN_MODEL_H
#define PIN_MODEL_H

#include <QPen>

#define DEFAULT_RADIUS 20

class PinModel
{
public:
    PinModel(qreal x, qreal y, qreal radius = DEFAULT_RADIUS, QPen contour = QPen(Qt::gray)) :
        m_contour(contour),
        m_radius(radius) { }

public:
    QPen m_contour;
    qreal m_x, m_y, m_radius;
};

#endif // PIN_MODEL_H
