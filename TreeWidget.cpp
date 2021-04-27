#include "TreeWidget.h"

#include <QColor>
#include <QPainter>

#include "Node.h"
#include "NodeWidget.h"

TreeWidget::TreeWidget(QWidget *parent)
    : QWidget(parent)
{

}

TreeWidget::~TreeWidget()
{

}

void TreeWidget::makeNodeWidget(Node *t)
{
    NodeWidget *nodeWidget = new NodeWidget(t, this);
    nodeWidget->setGeometry(10, 10, 90, 90);
    nodeWidget->move(100 * t->x(), 200 * t->y());
    nodes_.append(nodeWidget);
    nodeMap_[t] = nodeWidget;
}

void TreeWidget::makeTreeTraverse(Node *n)
{
    int mid = n->numChildren() / 2;
    for (int l = 0; l < mid; l++)
        makeTreeTraverse(n->child(l));
    makeNodeWidget(n);
    for (int r = mid; r < n->numChildren(); r++)
        makeTreeTraverse(n->child(r));
}

void TreeWidget::setTree(Node *node)
{
    tree_ = node;
    makeTreeTraverse(node);
}

void TreeWidget::paintEvent(QPaintEvent *e)
{
    QPainter p(this);

    p.setBrush(QColor("lightgray"));
    p.drawRect(0,0,width(),height());

    QPen pen = p.pen();
    pen.setColor("brown");
    pen.setWidth(5);
    p.setPen(pen);

    for (auto nodeWidget : findChildren<NodeWidget *>()) {
        Node *node = nodeWidget->node();
        for (auto nodeParent : node->parents()) {
            NodeWidget *nodeWidgetParent = nodeMap_[nodeParent];
            int childrenSpaces = nodeParent->numChildren() + 1;
            int childSpace = nodeParent->children().indexOf(node) + 1;
            p.drawLine(
                    // bottom parent pos
                    nodeWidgetParent->pos()
                      + QPoint(nodeWidgetParent->width() * childSpace / childrenSpaces,
                               nodeWidgetParent->height()),
                    // top child pos
                    nodeWidget->pos()
                      + QPoint(nodeWidget->width()/2,
                               0));
        }
    }

    QWidget::paintEvent(e);
}

