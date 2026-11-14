#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    AGate* andGate = new And(pen, inputs, 40.0, 50.0, 100.0, 100.0);
    m_scene = new Scene();
    m_scene->addItem(p1);
    m_scene->addItem(andGate);
    m_view = new View(m_scene);
    this->setCentralWidget(m_view);
}

MainWindow::~MainWindow()
{
    delete ui;
}
