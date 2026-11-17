#ifndef GATE_FACTORY_HPP
#define GATE_FACTORY_HPP

#include "gate.hpp"
#include "and.hpp"
#include "and_gate_model.hpp"
#include <string>

AGate* createViewGate(
    size_t idx,
    const std::string& name,
    qreal x,
    qreal y,
    const QVector<Pin*>& inputs,
    qreal length,
    qreal height,
    QPen contour);

AndGateModel* createModelGate(
    size_t idx,
    const std::string& name,
    qreal x,
    qreal y,
    QVector<PinModel*>& inputs,
    qreal length,
    qreal height,
    QPen contour);

#endif // GATE_FACTORY_HPP
