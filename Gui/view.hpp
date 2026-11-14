#ifndef VIEW_HPP
#define VIEW_HPP

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>

class View : public QGraphicsView
{
public:
    View(QGraphicsScene* parent = nullptr) : QGraphicsView(parent) { }
};

#endif // VIEW_HPP
