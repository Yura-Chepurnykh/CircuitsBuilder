#include "pin.hpp"

Pin::Pin(QPen contour, qreal x, qreal y, qreal radius) :
    m_contour(contour),
    m_posX(x),
    m_posY(y),
    m_radius(radius) { printf("create pin"); }

