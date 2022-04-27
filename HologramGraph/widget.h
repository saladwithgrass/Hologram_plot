#ifndef WIDGET_H
#define WIDGET_H
#pragma once
#include <QWidget>
#include <graphingwidget.h>
#include <segmentinputwidget.h>
#include <segmentfunction.h>
#include <vector>
#include <QVBoxLayout>
#include <QResizeEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    GraphingWidget* graph;
    std::vector<SegmentInputWidget*> inputWidgets;
    std::vector<SegmentFunction> segments;
    QVBoxLayout* inputsLayout = nullptr;
    QWidget* topRightWidget = nullptr;
    QWidget* centerWidget = nullptr;
    QWidget* segmentsFrame = nullptr, *okButton = nullptr;
public slots:
    void addInputSegment();
    void removeInputSegment();
    void updateData();
    void moveTopRight(QWidget* toMove);
    void centerHorizontally(QWidget* toCenter);
    void resizeEvent(QResizeEvent* event);
    void fillWithSegmentsAndButton(QWidget* segments, QWidget* button);
};
#endif // WIDGET_H
