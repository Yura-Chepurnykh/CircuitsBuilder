#ifndef SCENE_HPP
#define SCENE_HPP

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QWidget>

class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override
    {
        printf("Click to scene.\n");

        if (isCreate & event->button() == Qt::LeftButton)
        {
            printf("Submit for creation.\n");
            emit submitForCreation(event->scenePos());
            printf("POSITIONS ARE, %f, %f", event->scenePos().x(), event->scenePos().y());
            isCreate = false;
        }

        else if (event->button() == Qt::LeftButton)
        {
            printf("Find active item.\n");
            this->active = itemAt(event->scenePos(), QTransform());

            if (this->active)
                printf("Clicked to active item.\n");
        }
    }

    void keyPressEvent(QKeyEvent* event) override
    {
        if (event->key() == Qt::Key_C)
        {
            printf("C key pressed.\n");
            isCreate = true;
        }

        else if (event->key() == Qt::Key_D)
        {
            printf("D key pressed.\n");

            if (active)
            {
                printf("Delete item event.\n");
                emit deleteItem(active);
            }

            active = nullptr;
        }

        else if (event->key() == Qt::Key_U)
        {
            printf("Clicked Undo Key.\n");
            emit sendUndo();
        }

        else if (event->key() == Qt::Key_R)
        {
            printf("clicked Redo Key.\n");
            emit sendRedo();
        }
    }

signals:
    void submitForCreation(QPointF);
    void deleteItem(QGraphicsItem*);
    void sendUndo();
    void sendRedo();

public:
    bool isCreate = false;
    QGraphicsItem* active;
};

#endif // SCENE_HPP
