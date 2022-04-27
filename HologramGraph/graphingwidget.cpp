#include "graphingwidget.h"
#include <QDebug>

GraphingWidget::GraphingWidget(QWidget *parent) : QWidget(parent) {
}

GraphingWidget::GraphPainter::GraphPainter(QPaintDevice* device,
                                           const int& height_p, const int& width_p,
                                           const double& pxPerSecond_p = 15,
                                           const double& pxPerMm_p = 10,
                                           const int& padding_p = 10) : QPainter(device) {
    xDiff = padding_p;
    xLim = width_p;
    yDiff = height_p - padding_p;
    yLim = height_p;
    pxPerSecond = pxPerSecond_p;
    pxPerMm = pxPerMm_p;
}

void GraphingWidget::GraphPainter::drawFunction(double (*f)(const double&)) {
    QPoint previous(pxFromReal(0, f(0))), current;
    for (int x = pxFromX(0) + 1; x < xLim; ++x) {
        current = QPoint(x, pxFromY(f(xFromPx(x))));
        drawLine(current, previous);
        previous = current;
    }
}

void GraphingWidget::GraphPainter::drawFunction(double (*f)(const double &),
                                                const double &x0, const double &x1) {
    QPoint previous(pxFromReal(x0, f(x0))), current;
    for (int x = pxFromX(x0) + 1; x <= pxFromX(x1); ++x) {
        current = QPoint(x, pxFromY(f(xFromPx(x))));
        drawLine(current, previous);
        previous = current;
    }
}

void GraphingWidget::GraphPainter::drawFunction(const SegmentFunction& func) {
    QPoint previous(pxFromReal(func.getT0(), func.x(func.getT0()))), current;
    for (int x = pxFromX(func.getT0()) + 1; x <= pxFromX(func.getT1()); ++x) {
        current = QPoint(x, pxFromY(func.x(xFromPx(x))));
        drawLine(current, previous);
        previous = current;
    }
}

void GraphingWidget::GraphPainter::drawAxis() {
    drawLine(pxFromX(0), pxFromY(0), xLim, pxFromY(0));
    drawLine(pxFromX(0), 0, pxFromX(0), pxFromY(0));
    int xMark = pxFromX(1);
    int yMark = pxFromY(1);
    drawLine(xMark, pxFromY(0) + 1, xMark, pxFromY(0) - 1);
    drawLine(pxFromX(0) - 1, yMark, pxFromX(0) + 1, yMark);
}

void GraphingWidget::GraphPainter::drawGrid() {
    QPen previous = pen();
    setPen(Qt::DashLine);
    setPen(Qt::gray);
    for (int x = xDiff; x <= xLim; x += pxPerSecond) {
        drawLine(x, 0, x, yLim);
    }
    for (int y = yDiff; y >= 0; y -= pxPerMm) {
        drawLine(0, y, xLim, y);
    }
    setPen(previous);
}

void GraphingWidget::updateFunctions(const std::vector<SegmentFunction> &functions_p) {
    functions = functions_p;
    update();
}

void GraphingWidget::paintEvent(QPaintEvent *event) {
    GraphPainter painter(this, height(), width());
    painter.drawGrid();
    painter.drawAxis();
    qDebug() << functions.size();
    for (int co = 0; co < functions.size(); ++co) {
        painter.drawFunction(functions[co]);
    }
}
