#include "TreeWidget.h"

#include <QColor>
#include <QInputDialog>
#include <QPainter>

#include "Node.h"
#include "NodeWidget.h"

TreeWidget::TreeWidget(QWidget *parent)
    : QWidget(parent), tree_(nullptr), treeSize_(4, 4)
{

}

TreeWidget::~TreeWidget()
{

}

QSize TreeWidget::sizeHint() const
{
    return QSize(NodeWidget::NODE_WIDTH * (treeSize_.width() + 1),
            NodeWidget::NODE_HEIGHT * 2 * (treeSize_.height() + 1));
}

NodeWidget *TreeWidget::makeNodeWidget(Node *t)
{
    NodeWidget *nodeWidget = new NodeWidget(t, this);
    nodes_.append(nodeWidget);
    nodeMap_[t] = nodeWidget;
    return nodeWidget;
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

void TreeWidget::setTree(Node *tree)
{
    tree_ = tree;
    makeTreeTraverse(tree);
    for (auto nodeWidget : findChildren<NodeWidget *>()) {
        updateTree(nodeWidget);
    }
    updateGeometry();
}

void TreeWidget::updateTree(NodeWidget *nodeWidget)
{
    Node *node = nodeWidget->node();
    treeSize_ = QSize(qMax(treeSize_.width(), node->x()),
            qMax(treeSize_.height(), node->y()));
    resize(sizeHint());
    nodeWidget->move(NodeWidget::NODE_WIDTH * node->x(),
            NodeWidget::NODE_HEIGHT * 2 * node->y());
    nodeWidget->show();

}

void TreeWidget::addStringChild(const QPoint &pos)
{
    for (auto nodeWidget : findChildren<NodeWidget *>())
        if (nodeWidget->rect().contains(nodeWidget->mapFromGlobal(pos)))
            addChild(nodeWidget, Node::NodeType::String);
}

void TreeWidget::addDoubleChild(const QPoint &pos)
{
    for (auto nodeWidget : findChildren<NodeWidget *>())
        if (nodeWidget->rect().contains(nodeWidget->mapFromGlobal(pos)))
            addChild(nodeWidget, Node::NodeType::Float);
}

void TreeWidget::addChild(NodeWidget *nodeWidget, int nodeType)
{
    Node *node = nodeWidget->node();
    if (node->numChildren() >= node->maxChildren())
        return;
    bool ok;
    QString name = QInputDialog::getText(nodeWidget,
            "New child", "Name:", QLineEdit::Normal, QString(), &ok);
    if (ok && !name.isEmpty()) {
        Node *child = new Node(node);
        child->setName(name);
        child->setNodeType(static_cast<Node::NodeType>(nodeType));
        tree_->layout();
        makeNodeWidget(child);
        for (auto nodeWidget : findChildren<NodeWidget *>()) {
            updateTree(nodeWidget);
        }
        update();
    }
}

void TreeWidget::close()
{
    for (auto nodeWidget : findChildren<NodeWidget *>())
        delete nodeWidget;
    if (tree_) {
        delete tree_;
        tree_ = nullptr;
    }
    update();
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

