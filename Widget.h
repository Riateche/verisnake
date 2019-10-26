#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "Vsnake.h"
#include <QGraphicsRectItem>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private:
    Ui::Widget *ui;
    Vsnake m_processor;

    QVector<QVector<QGraphicsRectItem*>> m_rects;


    bool event(QEvent *event) override;
    void tick();
};
#endif // WIDGET_H
