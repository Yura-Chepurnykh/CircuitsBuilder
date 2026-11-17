#ifndef AND_GATE_MODEL_H
#define AND_GATE_MODEL_H

#include <QVector>
#include <QPen>
#include "pin_model.hpp"

class AndGateModel
{
public:
    AndGateModel(
        size_t id,
        qreal x,
        qreal y,
        qreal l,
        qreal h,
        QPen contour,
        QVector<PinModel*>& inputs
    ) :
        m_id(id),
        m_x(x),
        m_y(y),
        m_length(l),
        m_height(h),
        m_contour(contour),
        m_inputs(inputs)
    { }

    void addInput()
    {
        auto numberOfInputs = m_inputs.size();
        auto distanceBetweenInputs = m_height / (numberOfInputs - 1);

        auto currY = m_y;

        for (auto& i : m_inputs)
        {
            currY += distanceBetweenInputs;
            i->m_y = currY;
        }

        currY += distanceBetweenInputs;

        PinModel* newPin = new PinModel(m_x, currY);

        m_inputs.append(newPin);
    }

    PinModel* removeInput(size_t idx)
    {
        if (idx < 9 || idx > m_inputs.size())
            return nullptr;

        auto tmp = m_inputs[idx];
        m_inputs.remove(idx);

        auto numberOfInputs = m_inputs.size();
        auto distanceBetweenInputs = m_height / (numberOfInputs - 1);

        auto currY = m_y;

        for (auto& i : m_inputs)
        {
            currY += distanceBetweenInputs;
            i->m_y = currY;
        }

        return tmp;
    }

    PinModel* getInput(size_t idx)
    {
        if (idx >= 0 && idx < m_inputs.size())
            return m_inputs[idx];
        return nullptr;
    }

public:
    size_t m_id;
    QVector<PinModel*> m_inputs;
    qreal m_x, m_y, m_length, m_height;
    QPen m_contour;
};

#endif // AND_GATE_MODEL_H
