#pragma once

#include <QWidget>

#include <QMap>
#include <QPoint>
#include <QSize>
#include <QVector>

class QPaintEvent;

class Node;
class NodeWidget;

class TreeWidget: public QWidget
{
public:
    TreeWidget(QWidget *parent = nullptr);
    virtual ~TreeWidget();
    virtual QSize sizeHint() const override;
    void setTree(Node *);
    Node *tree() const { return tree_; }
    void addStringChild(const QPoint &);
    void addDoubleChild(const QPoint &);
    void close();
protected:
    virtual void paintEvent(QPaintEvent *) override;
private:
    Node *tree_;
    QSize treeSize_;
    void makeTreeTraverse(Node *);
    NodeWidget *makeNodeWidget(Node *);
    void addChild(NodeWidget *, int);
    void updateTree(NodeWidget *);
    QVector<NodeWidget *> nodes_;
    QMap<Node *, NodeWidget*> nodeMap_;
};
