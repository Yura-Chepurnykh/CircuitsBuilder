#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "create_gate_presenter.hpp"
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    GateLifeCyclePresenter* m_gateLifeCyclePresenter;
    AGate* m_gate;
    QGraphicsView* m_view;
    Scene* m_scene;
    CommandManager* m_manager;
    Items* m_models;
    Mapper* m_mapper;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
