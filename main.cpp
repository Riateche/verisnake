#include <QDebug>
#include <QTimer>
#include <iostream>
#include "Widget.h"
#include "Vsnake.h"
#include "verilated.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Widget w;
    w.show();


//    Vsnake top;

//    for(auto i = 0; i < 1000; i++) {
//        top.clk = i % 2;
//        top.reset = i == 1;
//        top.left = i < 500;
//        top.right = i > 500;
//        top.eval();
//        qDebug() << top.current_x << top.current_y;
//    }
    //QTimer::singleShot(500, &a, SLOT(quit()));
    return a.exec();
}
