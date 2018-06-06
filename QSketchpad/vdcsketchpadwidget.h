#ifndef VDCSKETCHPADWIDGET_H
#define VDCSKETCHPADWIDGET_H

#include <QWidget>
#include<QPainter>
#include <QList>
namespace Ui {
class VDCSketchpadWidget;
}

class VDCSketchpadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VDCSketchpadWidget(QWidget *parent = 0);
    ~VDCSketchpadWidget();
private:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void drawBackGround(QPainter&);         //绘制背景
    void drawUserDraw(QPainter&);           //用户绘制
private:
    Ui::VDCSketchpadWidget *ui;
    QVector<QLineF> m_lineFList;
    QPointF m_startPointF;
    QPointF m_endPointF;
    bool m_bValidDraw;  //有效绘画
    bool m_bStart;      //True 开始绘制 False 结束绘制
};

#endif // VDCSKETCHPADWIDGET_H
