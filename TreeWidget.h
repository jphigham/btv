#pragma once

#include <QWidget>

#include <QMap>
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
    void close();
protected:
    virtual void paintEvent(QPaintEvent *) override;
private:
    Node *tree_;
    QSize treeSize_;
    void makeTreeTraverse(Node *);
    void makeNodeWidget(Node *);
    QVector<NodeWidget *> nodes_;
    QMap<Node *, NodeWidget*> nodeMap_;
};
