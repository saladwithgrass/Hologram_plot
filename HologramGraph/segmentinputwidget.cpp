#include "segmentinputwidget.h"

SegmentInputWidget::SegmentInputWidget(QWidget* parent_p,
                                       QFrame* frame_p,
                                       QGridLayout* grid_p,
                                       QLineEdit* resVelInput_p,
                                       QLineEdit* endTimeInput_p,
                                       QLabel* resVelLabel_p,
                                       QLabel* endTimeLabel_p) :
                                       parent(parent_p),
                                       frame(frame_p), grid(grid_p),
                                       resVelInput(resVelInput_p),
                                       endTimeInput(endTimeInput_p),
                                       resVelLabel(resVelLabel_p),
                                       endTimeLabel(endTimeLabel_p)
                                    {
    toDelete = 0;
    // qDebug() << "input unit created " << (frame_p == nullptr);
    if (frame_p == nullptr) {
        toDelete = 1;
        frame = new QFrame(parent);
        grid = new QGridLayout(frame);

        resVelInput = new QLineEdit(grid->widget());
        endTimeInput = new QLineEdit(grid->widget());

        resVelLabel = new QLabel();
        endTimeLabel = new QLabel();
        resVelLabel->setText("Resulting velocity:");
        endTimeLabel->setText("End time:");

        grid->addWidget(endTimeLabel);
        grid->addWidget(resVelLabel);
        qDebug() << grid->columnCount() << grid->rowCount();
        grid->addWidget(endTimeInput, 0, 1);
        grid->addWidget(resVelInput, 1, 1);
        qDebug() << grid->columnCount() << grid->rowCount();

    }

}

SegmentInputWidget::~SegmentInputWidget() {
    if (toDelete) {
        delete resVelInput;
        delete endTimeInput;
        delete resVelLabel;
        delete endTimeLabel;
        delete grid;
        delete frame;

    }
}
