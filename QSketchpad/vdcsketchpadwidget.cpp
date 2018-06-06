#include "vdcsketchpadwidget.h"
#include "ui_vdcsketchpadwidget.h"
#include<QMouseEvent>
#include<QImage>
#include<QDebug>
VDCSketchpadWidget::VDCSketchpadWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VDCSketchpadWidget),m_bStart(true),m_lineFList(),m_bValidDraw(true)
{
    ui->setupUi(this);
    setWindowFlags(Qt::BypassWindowManagerHint|Qt::Drawer);//全无边框;画板
    setWindowState(Qt::WindowFullScreen);   //全屏
    setAttribute(Qt::WA_OpaquePaintEvent );//update 不擦除界面
    m_startPointF=m_endPointF=QPoint(0,0);

}

VDCSketchpadWidget::~VDCSketchpadWidget()
{
    delete ui;
}
void VDCSketchpadWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(m_bStart)
    {
        drawBackGround(painter);
        m_bStart =false;
    }
    else
        drawUserDraw(painter);
}
void VDCSketchpadWidget::mousePressEvent(QMouseEvent *event)
{
    m_bValidDraw = event->button() == Qt::LeftButton;
    if(m_bValidDraw)
        m_startPointF =event->pos();
    m_lineFList.clear();
}
void VDCSketchpadWidget::mouseReleaseEvent(QMouseEvent *event)
{

    if(event->button() == Qt::RightButton)
    {
        m_bStart =true;
        update();
    }
}
void VDCSketchpadWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bValidDraw)
    {
        m_endPointF =event->pos();

        m_lineFList<<QLineF(m_startPointF,m_endPointF);
        m_startPointF = m_endPointF;
        qDebug()<< "point List "<<m_lineFList.size();
        update();
    }

}
void VDCSketchpadWidget::drawBackGround(QPainter&painter)
{
    painter.save();
    QPen pen; //画笔
    pen.setColor(Qt::white);
    QBrush brush(Qt::white); //画刷
    painter.setPen(pen); //添加画笔
    painter.setBrush(brush); //添加画刷
    painter.drawRect(geometry()); //绘制矩形
    painter.restore();
}
void VDCSketchpadWidget::drawUserDraw(QPainter &userPaint)
{

    userPaint.save();
    QPen pen; //画笔
    pen.setColor(Qt::black);
    pen.setWidth(6);    //设置画笔
    QBrush brush(Qt::black); //画刷
    userPaint.setPen(pen);
    userPaint.setBrush(brush);
    userPaint.drawLines(m_lineFList);
    userPaint.restore();
}
