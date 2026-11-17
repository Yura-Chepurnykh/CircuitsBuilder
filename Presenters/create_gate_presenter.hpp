#ifndef CREATE_GATE_PRESENTER_HPP
#define CREATE_GATE_PRESENTER_HPP

#include <QPen>
#include <QGraphicsItem>
#include "gate_factory.hpp"
#include "scene.hpp"
#include "items.hpp"
#include "model_to_views.hpp"
#include "gate.hpp"
#include <stack>
#include <QObject>

class CreateGateCommand;

struct ICommand
{
    virtual void action() = 0;
    virtual void undo() = 0;
};

class CreateGateAction
{
public:
    CreateGateAction(
        Scene& sceneView,
        Items& models,
        Mapper& mapper,
        const std::string& name,
        qreal x,
        qreal y,
        qreal length,
        qreal height,
        QPen pen,
        const QVector<Pin*>& inputs
    ) :
        m_viewScene(sceneView),
        m_models(models),
        m_mapper(mapper),
        m_x(x),
        m_y(y),
        m_length(length),
        m_height(height),
        m_pen(pen),
        m_inputs(inputs),
        m_name(name)

    {
        printf("Get x and y in CreateGateAction in CTOR %f, %f\n", m_x, m_y);
    }

    void action()
    {
        printf("CreateGateAction(...).\n");

        // dummy
        QVector<PinModel*> inputModels;
        QVector<Pin*> inputViews;

        printf("Get x and y in CreateGateAction %f, %f\n", m_x, m_y);

        m_createdViewGate = createViewGate(m_mapper.view_id++, m_name, m_x, m_y, inputViews, m_length, m_height, m_pen);
        AndGateModel* newModelGate = createModelGate(m_mapper.model_id++, m_name, m_x, m_y, inputModels, m_length, m_height, m_pen);
        m_mapper.modelToView[newModelGate->m_id] = m_createdViewGate->m_id;
        m_mapper.viewToModel[m_createdViewGate->m_id] = newModelGate->m_id;
        m_models.addItem(newModelGate);
        m_viewScene.addItem(m_createdViewGate);
        m_viewScene.update();
    }

public:
    std::string m_name;
    qreal m_x, m_y, m_length, m_height;
    QPen m_pen;
    QVector<Pin*> m_inputs;

    AGate* m_createdViewGate;

    Mapper& m_mapper;
    Scene& m_viewScene;
    Items& m_models;
};

class DeleteGateAction
{
public:
    DeleteGateAction(QGraphicsItem* item, Mapper& mapper, Scene& sceneView, Items& models) :
        m_item(item), m_mapper(mapper), m_viewScene(sceneView), m_models(models) { }

    void setItem(QGraphicsItem* item)
    {
        m_item = item;
    }

    void action()
    {
        printf("DeleteGateAction(...).\n");

        auto allItems = m_viewScene.items();

        if (!m_item)
            printf("ITEM IS EMPTY.\n");

        auto removedId = -1;

        for (auto& item : allItems)
        {
            if (m_item == item)
            {
                printf("removed ITEM\n");
                m_viewScene.removeItem(m_item);
                m_viewScene.update();

                if (auto item = dynamic_cast<And*>(m_item); item != nullptr)
                    removedId = item->m_id;
            }
        }

        //m_viewScene.removeItem(m_item);
        //m_viewScene.update();

        m_models.removeItem(m_mapper.viewToModel[removedId]);
    }

private:
    Mapper& m_mapper;
    QGraphicsItem* m_item;
    Scene& m_viewScene;
    Items& m_models;
};

class CreateGateCommand : public ICommand
{
public:
    CreateGateCommand(CreateGateAction* action, DeleteGateAction* undo) :
        m_action(action), m_undo(undo) { }

    void action()
    {
        m_action->action();
        m_undo->setItem(m_action->m_createdViewGate);
    }

    void undo()
    {
        m_undo->action();
    }

    CreateGateAction* m_action;
    DeleteGateAction* m_undo;
};

class DeleteGateCommand : public ICommand
{
public:
    DeleteGateCommand(DeleteGateAction* action, CreateGateAction* undo) :
        m_action(action), m_undo(undo) { }

    void action()
    {
        m_action->action();
    }

    void undo()
    {
        m_undo->action();
        m_action->setItem(m_undo->m_createdViewGate);
    }

    DeleteGateAction* m_action;
    CreateGateAction* m_undo;
};

class CommandManager : public QObject
{
    Q_OBJECT

public:
    CommandManager(Scene& sceneView, Items& models) : m_sceneView(sceneView), m_models(models)
    {
        connect(&sceneView, &Scene::sendUndo, this, &CommandManager::undo);
        connect(&sceneView, &Scene::sendRedo, this, &CommandManager::redo);
    }

    void action(ICommand* cmd, ICommand* undoCmd)
    {
        printf("action(...)\n");

        if (auto a = dynamic_cast<CreateGateCommand*>(cmd); a != nullptr)
        {
            printf("a coordinates YUUUU %f, %f\n\n", a->m_action->m_x, a->m_action->m_y);
        }

        cmd->action();
        m_undoStack.push(cmd);

        if (!m_redoStack.empty())
        {
            delete m_redoStack.top();
            m_redoStack.pop();
        }
    }

public slots:

    void undo()
    {
        printf("undo slot\n");

        if (!m_undoStack.empty())
        {
            printf("undo slot if\n");

            auto top = m_undoStack.top();

            top->undo();
            m_redoStack.push(top);
            m_undoStack.pop();

        }
    }

    void redo()
    {
        if (!m_redoStack.empty())
        {
            auto top = m_redoStack.top();
            m_redoStack.pop();

            m_undoStack.push(top);
            top->action();
        }
    }

public:
    std::stack<ICommand*> m_undoStack;
    std::stack<ICommand*> m_redoStack;

    Scene& m_sceneView;
    Items& m_models;
};

class GateLifeCyclePresenter : public QObject
{
    Q_OBJECT

public:
    GateLifeCyclePresenter(Scene& sceneView, Items& models, Mapper& mapper, CommandManager& manager) :
        m_sceneView(sceneView), m_models(models), m_mapper(mapper), m_manager(manager)
    {
        connect(&m_sceneView, &Scene::submitForCreation, this, &GateLifeCyclePresenter::getPositionForCreation);
        connect(&m_sceneView, &Scene::deleteItem, this, &GateLifeCyclePresenter::getDeleteGate);
    }

public slots:
    void getPositionForCreation(QPointF pos)
    {
        printf("Get position for creation %f, %f\n", pos.x(), pos.y());
        qDebug() << "Get position for creation" << pos.x() << " " << pos.y() << '\n';

        // dummy
        QVector<Pin*> inputs;

        CreateGateAction* createAction = new CreateGateAction(m_sceneView, m_models, m_mapper, "And", pos.x(), pos.y(), 40, 40, QPen(Qt::darkRed), inputs);
        DeleteGateAction* deleteAction = new DeleteGateAction(m_active, m_mapper, m_sceneView, m_models);

        CreateGateCommand* createCmd = new CreateGateCommand(createAction, deleteAction);
        DeleteGateCommand* deleteCmd = new DeleteGateCommand(deleteAction, createAction);

        m_manager.action(createCmd, deleteCmd);
    }

    void getDeleteGate(QGraphicsItem* item)
    {
        printf("Get delete gate\n");

        m_active = item;

        printf("m_active address %p\n", m_active);

        // dummy
        QVector<Pin*> inputs;

        CreateGateAction* createAction = new CreateGateAction(m_sceneView, m_models, m_mapper, "And", item->x(), item->y(), 40, 40, QPen(Qt::darkRed), inputs);
        DeleteGateAction* deleteAction = new DeleteGateAction(m_active, m_mapper, m_sceneView, m_models);

        CreateGateCommand* createCmd = new CreateGateCommand(createAction, deleteAction);
        DeleteGateCommand* deleteCmd = new DeleteGateCommand(deleteAction, createAction);

        m_manager.action(deleteCmd, createCmd);
    }

private:
    CommandManager& m_manager;
    Mapper& m_mapper;
    Scene& m_sceneView;
    Items& m_models;
    QGraphicsItem* m_active;
};



#endif // CREATE_GATE_PRESENTER_HPP
