#include "TreeWidget.h"

#include <QColor>
#include <QPainter>

#include "Node.h"
#include "NodeWidget.h"

TreeWidget::TreeWidget(QWidget *parent)
    : QWidget(parent), treeSize_(4, 4)
{

}

TreeWidget::~TreeWidget()
{

}

QSize TreeWidget::sizeHint() const
{
    return QSize(NodeWidget::NODE_WIDTH * (treeSize_.width() + 1),
            NodeWidget::NODE_HEIGHT * 2 * treeSize_.height());
}

void TreeWidget::makeNodeWidget(Node *t)
{
    NodeWidget *nodeWidget = new NodeWidget(t, this);
    nodes_.append(nodeWidget);
    nodeMap_[t] = nodeWidget;

    nodeWidget->move(NodeWidget::NODE_WIDTH * t->x(), NodeWidget::NODE_HEIGHT * 2 * t->y());
    treeSize_ = QSize(qMax(treeSize_.width(), t->x()), qMax(treeSize_.height(), t->y()));
    updateGeometry();
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
    p.setRenderHint(QPainter::Antialiasing);

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

