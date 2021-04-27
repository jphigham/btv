#pragma once

#include <QSlider>

class DoubleSlider : public QSlider
{
    Q_OBJECT
public:
    DoubleSlider(QWidget *parent = nullptr);
    virtual ~DoubleSlider();

    void setDoubleRange(double, double);
    void setDoubleValue(double);
    double doubleValue() const;
signals:
    void doubleValueChanged(float);
public slots:
    void intValueChanged(int);
private:
    double doubleMinimum_;
    double doubleMaximum_;
};

