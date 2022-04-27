#include "widget.h"
#include "ui_widget.h"
#include "segmentinputwidget.cpp"
#include "segmentfunction.cpp"

void oneBelowAnother(QWidget* other, QWidget* one) {
    one->move(one->x(), other->y() + other->height());
}

void alignLeft(QWidget* one, QWidget* other) {
    other->move(one->x(), other->y());
}

void alignRight(QWidget* one, QWidget* other) {
    other->move(one->x() + one->width(), other->y());
}

void equalizeWidths(QWidget* one, QWidget* other) {
    other->setGeometry(other->x(), other->y(),
                       one->width(), other->height());
}

inline void verticalLayout(QWidget* one, QWidget* other) {
    oneBelowAnother(one, other);
    alignLeft(one, other);
    equalizeWidths(one, other);
}

void Widget::centerHorizontally(QWidget* toCenter) {
    centerWidget = toCenter;
    toCenter->move(width() / 2 - toCenter->width()/2, toCenter->y());
}


void Widget::moveTopRight(QWidget* toMove) {
    topRightWidget = toMove;
    toMove->move(width() - toMove->width(), 0);
}

void resizeLayout(const int& w, const int& h, QVBoxLayout* box) {
    QRect prevGeom = box->geometry();
    prevGeom.setHeight(h);
    prevGeom.setWidth(w);
    box->setGeometry(prevGeom);
}

void Widget::fillWithSegmentsAndButton(QWidget* segments, QWidget* button) {
    segments->move(segments->x(), 0);
    segments->resize(segments->width(), height() - button->height());
    resizeLayout(segments->width(), segments->height(), ui->inputsLayout);
}

void Widget::resizeEvent(QResizeEvent* event) {
    ui->inputsLayout->setSizeConstraint(ui->inputsLayout->SetNoConstraint);
    if (topRightWidget != nullptr) moveTopRight(topRightWidget);
    if (centerWidget != nullptr) centerHorizontally(centerWidget);
    fillWithSegmentsAndButton(ui->inputsFrame, ui->okButton);
    alignRight(ui->inputsFrame, ui->buttonsFrame);
    oneBelowAnother(ui->inputsFrame, ui->buttonsFrame);
    verticalLayout(ui->inputsFrame, ui->okButton);
}

void Widget::addInputSegment() {
    inputWidgets.push_back(new SegmentInputWidget(this));
    inputsLayout->addWidget(inputWidgets.back()->getFrame());
    int newHeight = inputsLayout->geometry().height() +
            inputWidgets.back()->getFrame()->geometry().height();
    inputsLayout->geometry().setHeight(newHeight);
    qDebug() << "add input";

}

void Widget::removeInputSegment() {
    inputsLayout->removeWidget(inputWidgets.back()->getFrame());
    delete inputWidgets.back();
    inputWidgets.pop_back();
    qDebug() << "remove input";
}

void Widget::updateData() {
    segments.clear();
    SegmentInputWidget* cur = nullptr;
    double prevX0 = 0, prevT1 = 0, prevV1 = 0;
    for (int co = 0; co < inputWidgets.size(); ++co) {
        cur = inputWidgets[co];
        segments.push_back(SegmentFunction(prevT1, cur->getEndTime(), prevV1,
                                           cur->getResultingVelocity(), prevX0));
        prevT1 = cur->getEndTime();
        prevX0 = segments.back().x(prevT1);
        prevV1 = cur->getResultingVelocity();
    }
    graph->updateFunctions(segments);
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    graph = new GraphingWidget();
    graph->show();
    inputsLayout = ui->inputsLayout;
    connect(ui->addSegmentButton, SIGNAL(clicked()), this, SLOT(addInputSegment()));
    connect(ui->removeSegmentButton, SIGNAL(clicked()), this, SLOT(removeInputSegment()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(updateData()));
    addInputSegment();
    centerHorizontally(ui->inputsFrame);
    moveTopRight(ui->accelerationLimitFrame);
    ui->inputsFrame->setFrameStyle(QFrame::Panel | QFrame::Raised);
    ui->inputsLayout->setMargin(0);
   //  wdg->moveTo(300, 200);
}

Widget::~Widget()
{
    delete ui;
}

