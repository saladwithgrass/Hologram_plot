#ifndef GRAPHINGWIDGET_H
#define GRAPHINGWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <math.h>
#include <segmentfunction.h>
#include <vector>

class GraphingWidget : public QWidget
{
    Q_OBJECT

private:
    std::vector<SegmentFunction> functions;

public:
    explicit GraphingWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* event) override;
    void updateFunctions(const std::vector<SegmentFunction>& functions_p);

    class GraphPainter : public QPainter {
    private:
        int yDiff, xDiff, xLim, yLim;
        double pxPerMm, pxPerSecond;
    public:
        void setXDiff(const int& newDiff) {
            xDiff = newDiff;
        }
        void setYDiff(const int& newDiff) {
            yDiff = newDiff;
        }
        void setPxPerMm(const double& newVal) {
            pxPerMm = newVal;
        }

        inline int pxFromX(const double& x) { return xDiff + x * pxPerSecond; }
        inline int pxFromY(const double& y) { return yDiff - y * pxPerMm; }
        QPoint pxFromReal(const QPoint& point) {
            return QPoint(pxFromX(point.x()), pxFromY(point.y()));
        }
        QPoint pxFromReal(const double& x, const double& y) {
            return QPoint(pxFromX(x), pxFromY(y));
        }

        inline double xFromPx(const int& px) {
            return (px - xDiff) / pxPerSecond;
        }

        inline double yFromPx(const int& px) {
            return -(px - yDiff) / pxPerMm;
        }

        GraphPainter(QPaintDevice* parent, const int& height, const int& width,
                     const double& pxPerSecond_p, const double& pxPerMm_p, const int& padding);
        void drawFunction(double (*f)(const double&));
        void drawFunction(double (*const f)(const double&), const double& x0, const double& x1);
        void drawFunction(const SegmentFunction& func);
        void drawAxis();
        void drawGrid();
    };

signals:

};

#endif // GRAPHINGWIDGET_H
