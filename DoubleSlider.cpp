#include "DoubleSlider.h"

#include <QDebug>

DoubleSlider::DoubleSlider(QWidget *parent)
    : QSlider(Qt::Horizontal, parent)
{
    connect(this, &QSlider::valueChanged, this, &DoubleSlider::intValueChanged);
}

DoubleSlider::~DoubleSlider()
{

}

void DoubleSlider::setDoubleRange(double doubleMinimum, double doubleMaximum)
{
    doubleMinimum_ = doubleMinimum;
    doubleMaximum_ = doubleMaximum;
}

void DoubleSlider::setDoubleValue(double doubleValue)
{
    emit doubleValueChanged(doubleValue);
}

double DoubleSlider::doubleValue() const
{
    double frac = double(value() - minimum()) / double(maximum() - minimum());
    return doubleMinimum_ + frac * (doubleMaximum_ - doubleMinimum_);
}

void DoubleSlider::intValueChanged(int)
{
    emit doubleValueChanged(doubleValue());
}

