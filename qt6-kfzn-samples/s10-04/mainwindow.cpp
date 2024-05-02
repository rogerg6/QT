#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lab_view_cord_ = new QLabel("View 坐标", this);
    lab_view_cord_->setMinimumWidth(150);
    ui->statusBar->addWidget(lab_view_cord_);

    lab_scene_cord_ = new QLabel("Scene 坐标", this);
    lab_scene_cord_->setMinimumWidth(150);
    ui->statusBar->addWidget(lab_scene_cord_);

    lab_item_cord_ = new QLabel("Item 坐标", this);
    lab_item_cord_->setMinimumWidth(150);
    ui->statusBar->addWidget(lab_item_cord_);

    // TGraphicsView组件view的设置
    ui->view->setCursor(Qt::CrossCursor);       // 十字形光标
    ui->view->setMouseTracking(true);               // 开启鼠标追踪
    ui->view->setDragMode(QGraphicsView::RubberBandDrag);   // 矩形选择框
    connect(ui->view, SIGNAL(mouseMovePoint(QPoint)), this, SLOT(do_mouseMovePoint(QPoint)));
    connect(ui->view, SIGNAL(mouseClicked(QPoint)), this, SLOT(do_mouseClicked(QPoint)));

    // 图形/视图架构初始化
    iniGraphicsSystem();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iniGraphicsSystem() {
    QRectF rect(-200,-100, 400, 200);
    scene_ = new QGraphicsScene(rect, this);    // 场景坐标系设置
    ui->view->setScene(scene_);                 // 为视图设置场景

    // 1. 画一个矩形框，其大小等于场景大小
    QGraphicsRectItem *item = new QGraphicsRectItem(rect);

    // 可选择，可获得焦点。但不能移动
    item->setFlags(QGraphicsItem::ItemIsSelectable |
                   QGraphicsItem::ItemIsFocusable);
    QPen pen;
    pen.setWidth(2);
    item->setPen(pen);
    scene_->addItem(item);

    // 2. 一个位于场景中心的椭圆，测试局部坐标
    QGraphicsEllipseItem *item2 = new QGraphicsEllipseItem(-100,-50,200,100);
    item2->setPos(0,0);     // 图形项在场景中的坐标
    item2->setBrush(QBrush(Qt::blue));
    item2->setFlag(QGraphicsItem::ItemIsMovable);       // 可移动
    item2->setFlag(QGraphicsItem::ItemIsSelectable);    // 可选择
    item2->setFlag(QGraphicsItem::ItemIsFocusable);     // 可获得焦点
    scene_->addItem(item2);

    // 3. 一个圆，中心位于场景边缘
    QGraphicsEllipseItem *item3 = new QGraphicsEllipseItem(-50,-50,100,100);
    item3->setPos(rect.right(), rect.bottom());     // 图形项在场景中的坐标
    item3->setBrush(QBrush(Qt::red));
    item3->setFlag(QGraphicsItem::ItemIsMovable);       // 可移动
    item3->setFlag(QGraphicsItem::ItemIsSelectable);    // 可选择
    item3->setFlag(QGraphicsItem::ItemIsFocusable);     // 可获得焦点
    scene_->addItem(item3);

    scene_->clearSelection();
}

void MainWindow::resizeEvent(QResizeEvent *event){
    QString str = QString::asprintf("Graphics View坐标，左上角总是(0,0),宽度=%d,高度=%d",\
                   ui->view->width(), ui->view->height());
    ui->labViewSize->setText(str);

    QRectF rectF = ui->view->sceneRect();   // 场景的矩形区
    QString str2 = QString::asprintf("QGraphicsView::sceneRect=(Left,Top,Width,Height)"
          "=%.0f,%.0f,%.0f,%.0f", rectF.left(), rectF.top(), rectF.width(), rectF.height());
    ui->labSceneRect->setText(str2);
    event->accept();
}

void MainWindow::do_mouseMovePoint(QPoint point){
    lab_view_cord_->setText(QString::asprintf("View坐标：%d,%d", point.x(), point.y()));
    QPointF point_scene = ui->view->mapToScene(point);  // view坐标变换为scene坐标
    lab_scene_cord_->setText(QString::asprintf("Scene坐标：%.0f,%.0f", \
                   point_scene.x(), point_scene.y()));
}

void MainWindow::do_mouseClicked(QPoint point){
    QPointF point_scene = ui->view->mapToScene(point);
    QGraphicsItem *item = nullptr;
    item = scene_->itemAt(point_scene, ui->view->transform());  // 获取光标处的图形项

    if (item != nullptr) {
        QPointF point_item = item->mapFromScene(point_scene);
        lab_item_cord_->setText(QString::asprintf("Item坐标：%.0f,%.0f", \
                            point_item.x(), point_item.y()));
    }
}

