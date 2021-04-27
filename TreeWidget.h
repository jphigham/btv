#pragma once

#include <QWidget>

#include <QMap>
#include <QVector>

class QPaintEvent;

class Node;
class NodeWidget;

class TreeWidget: public QWidget
{
public:
    TreeWidget(QWidget *parent = nullptr);
    virtual ~TreeWidget();
    void setTree(Node *);
protected:
    virtual void paintEvent(QPaintEvent *) override;
private:
    Node *tree_;
    void makeTreeTraverse(Node *);
    void makeNodeWidget(Node *);
    QVector<NodeWidget *> nodes_;
    QMap<Node *, NodeWidget*> nodeMap_;
};
