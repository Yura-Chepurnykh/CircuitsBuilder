#include "gate_factory.hpp"

AGate* createViewGate(
    size_t idx,
    const std::string& name,
    qreal x,
    qreal y,
    const QVector<Pin*>& inputs,
    qreal length,
    qreal height,
    QPen contour)
{
    if (name == "And")
        return new And(idx, contour, inputs, x, y, length, height);
    return nullptr;
}

AndGateModel* createModelGate(
    size_t idx,
    const std::string& name,
    qreal x,
    qreal y,
    QVector<PinModel*>& inputs,
    qreal length,
    qreal height,
    QPen contour)
{
    if (name == "And")
        return new AndGateModel(idx, x, y, length, height, contour, inputs);
    return nullptr;
}
