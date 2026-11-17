#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //m_gateLifeCyclePresenter = new GateLifeCyclePresenter();

    printf("Create mainwindow\n");

    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::red);
    Pin* p1 = new Pin(pen, 20.0, 30.0, 10.0);
    Pin* p2 = new Pin(pen, 40.0, 70.0, 10.0);
    Pin* p3 = new Pin(pen, 90.0, 20.0, 10.0);
    QVector<Pin*> inputs{ p1, p2, p3 };
    //inputs.append(p1);
    //inputs.append(p2);
    //inputs.append(p3);

    AGate* andGate = new And(1, pen, inputs, 40.0, 50.0, 100.0, 100.0);
    m_scene = new Scene();
    m_scene->addItem(p1);
    m_scene->addItem(andGate);
    m_view = new QGraphicsView(m_scene);
    m_view->show();

    m_scene->setSceneRect(0, 0, 1920, 1080);

    m_models = new Items();
    m_mapper = new Mapper();
    m_manager = new CommandManager(*m_scene, *m_models);
    m_gateLifeCyclePresenter = new GateLifeCyclePresenter(*m_scene, *m_models, *m_mapper, *m_manager);

    this->setCentralWidget(m_view);
}

MainWindow::~MainWindow()
{
    delete ui;
}
