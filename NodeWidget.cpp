#include "NodeWidget.h"

#include <QColor>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QSpacerItem>
#include <QVBoxLayout>

#include "DoubleSlider.h"
#include "Node.h"

NodeWidget::NodeWidget(Node *node, QWidget *parent)
    : QWidget(parent), node_(node)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    name_ = new QLabel(this);
    QPalette palette = name_->palette();
    palette.setColor(QPalette::WindowText, QColor("white"));
    name_->setPalette(palette);
    name_->setText(node->name());

    layout->addWidget(name_, 0, Qt::AlignHCenter);
    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));

    switch (node->nodeType()) {
    case Node::NodeType::Float:
        doubleSlider_ = new DoubleSlider(this);
        doubleSlider_->setRange(0,100);
        doubleSlider_->setDoubleRange(-1000.0, 1000.0);
        doubleSlider_->setDoubleValue(node->value().toDouble());
        connect(doubleSlider_, &DoubleSlider::doubleValueChanged, [=] (double dv) {
            node_->setValue(dv);
        });
        lineEdit_ = nullptr;
        layout->addWidget(doubleSlider_, 0, Qt::AlignHCenter);
        break;
    case Node::NodeType::String:
        doubleSlider_ = nullptr;
        lineEdit_ = new QLineEdit(this);
        lineEdit_->setText(node->value().toString());
        connect(lineEdit_, &QLineEdit::textChanged, [=] (const QString &text) {
           node_->setValue(text);
        });
        layout->addWidget(lineEdit_, 0, Qt::AlignHCenter);
        break;
    default:
        doubleSlider_ = nullptr;
        lineEdit_ = nullptr;
    }
}

NodeWidget::~NodeWidget()
{

}

void NodeWidget::paintEvent(QPaintEvent *e)
{
    QPainter p(this);

    p.setBrush(QColor("darkgray"));
    p.drawRect(0,0,width(),height());
    p.setBrush(QColor("darkblue"));
    p.drawRect(0,0,width()/20, height());

    QWidget::paintEvent(e);
}
