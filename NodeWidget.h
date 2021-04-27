#pragma once

#include <QWidget>

class QLabel;
class QLineEdit;
class QPaintEvent;

class DoubleSlider;
class Node;

class NodeWidget : public QWidget
{
    Q_OBJECT
public:
    static const int NODE_WIDTH = 100;
    static const int NODE_HEIGHT = 100;
    NodeWidget(Node *, QWidget *parent = nullptr);
    virtual ~NodeWidget();
    virtual QSize sizeHint() const override { return QSize(NODE_WIDTH, NODE_HEIGHT); }
    const Node *node() const { return node_; }
    Node *node() { return node_; }
protected:
    virtual void paintEvent(QPaintEvent *) override;
private:
    Node *node_;
    QLabel *name_;
    DoubleSlider *doubleSlider_;
    QLineEdit *lineEdit_;
};
