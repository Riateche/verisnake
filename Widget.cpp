#include "Widget.h"
#include "ui_Widget.h"
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>

const int WIDTH = 20;
const int HEIGHT = 30;


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->view->setScene(new QGraphicsScene());

    for(auto y = 0; y < HEIGHT; y++) {
        QVector<QGraphicsRectItem*> vec;
        for(auto x = 0; x < WIDTH; x++) {
            auto rect = new QGraphicsRectItem(QRectF(0, 0, 1, 1));
            rect->setPos(x, y);
            rect->setBrush(Qt::white);
            QPen pen(Qt::black);
            pen.setCosmetic(true);
            rect->setPen(pen);
            ui->view->scene()->addItem(rect);
            vec << rect;
        }
        m_rects << vec;
    }

    ui->view->scale(30, 30);

    m_processor.clk = false;
    m_processor.reset = false;
    m_processor.eval();
    m_processor.clk = true;
    m_processor.reset = true;
    m_processor.eval();
    m_processor.clk = false;
    m_processor.reset = false;

    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::tick);
    timer->start(10);
}

Widget::~Widget() {
    delete ui;
}

bool Widget::event(QEvent *event) {
    auto key_event = dynamic_cast<QKeyEvent*>(event);
    if (!key_event) { return QWidget::event(event); }
    auto is_press = event->type() == QEvent::KeyPress;
    switch (key_event->key()) {
    case Qt::Key_Left:
        m_processor.left = is_press;
        break;
    case Qt::Key_Right:
        m_processor.right = is_press;
        break;
    case Qt::Key_Up:
        m_processor.up = is_press;
        break;
    case Qt::Key_Down:
        m_processor.down = is_press;
        break;
    case Qt::Key_R:
        m_processor.reset = is_press;
        break;
    }
    return QWidget::event(event);
}

void Widget::tick() {
    for(uint8_t y = 0; y < HEIGHT; y++) {
        for(uint8_t x = 0; x < WIDTH; x++) {
            m_processor.video_x = x;
            m_processor.video_y = y;
            m_processor.video_clk = true;
            m_processor.eval();
            m_processor.video_clk = false;
            m_processor.eval();
            m_rects[y][x]->setBrush(QColor(QRgb(m_processor.video_output)));
        }
    }

    m_processor.clk = true;
    m_processor.eval();
    m_processor.clk = false;
    m_processor.eval();

    QString debug;
//    QDebug(&debug) << "next_x" << (m_processor.snake__DOT__next_x_plus_one - 1);
//    QDebug(&debug) << "dx" << (m_processor.snake__DOT__dx);

    ui->debug->setText(debug);
}
