#ifndef SEGMENTINPUTWIDGET_H
#define SEGMENTINPUTWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QFrame>
#include <QDebug>

class SegmentInputWidget {
private:
    QWidget* parent;
    QGridLayout* grid;
    QFrame* frame;
    QLineEdit *resVelInput, *endTimeInput;
    QLabel *resVelLabel, *endTimeLabel;
    bool toDelete;
public:
    SegmentInputWidget(QWidget* parent_p,
                       QFrame* frame_p = nullptr,
                       QGridLayout* grid_p  = nullptr,
                       QLineEdit* resVelInput_p = nullptr,
                       QLineEdit* endTimeInput_p = nullptr,
                       QLabel* resVelLabel_p = nullptr,
                       QLabel* endTimeLabel_p = nullptr);
    ~SegmentInputWidget();

    void setrResVelLabel(QLabel* label) {
        resVelLabel = label;
        resVelLabel->setText("Maximum velocity:");
    }
    void setEndTimeLabel(QLabel* label) {
        endTimeLabel = label;
        endTimeLabel->setText("End time:");
    }

    double getResultingVelocity() {
        return resVelInput->text().toDouble();
    }
    double getEndTime() {
        return endTimeInput->text().toDouble();
    }

    void moveTo(const QPoint& newPoint) {
        grid->geometry().moveTo(newPoint);
    }

    void moveTo(const int& x, const int& y) {
        grid->geometry().moveTo(x, y);
    }

    QFrame* getFrame() { return frame; }

};

#endif // SEGMENTINPUTWIDGET_H
