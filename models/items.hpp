#ifndef ITEMS_HPP
#define ITEMS_HPP

#include <QVector>
#include "and_gate_model.hpp"

class Items
{
public:
    void addItem(AndGateModel* andGate)
    {
        m_gates.append(andGate);
    }

    void removeItem(size_t id)
    {
        for (size_t i = 0; i < m_gates.size(); ++i)
            if (m_gates[i]->m_id == id)
                m_gates.remove(i);
    }

private:
    QVector<AndGateModel*> m_gates;
};

#endif // ITEMS_HPP
