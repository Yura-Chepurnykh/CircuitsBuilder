#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "view.hpp"
#include "scene.hpp"
#include "gate.hpp"
#include "and.hpp"
#include <QVector>

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
    AGate* m_gate;
    QGraphicsView* m_view;
    QGraphicsScene* m_scene;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
