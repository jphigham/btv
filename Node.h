#pragma once

#include <QColor>
#include <QJsonObject>
#include <QString>
#include <QUuid>
#include <QVariant>
#include <QVector>

//! Node
/*! \class Node
    \brief Represents a node with parent(s) and children
 */
class Node
{
public:
    enum NodeType {String, Float};

    Node(Node * = nullptr);
    virtual ~Node();

    void setName(const QString &name) { name_ = name; }
    const QString &name() const { return name_; }

    void setId(const QString &id) { id_ = id; }
    const QUuid &id() const { return id_; }

    void setNodeType(NodeType nodeType) { nodeType_ = nodeType; }
    NodeType nodeType() const { return nodeType_; }

    void setX(int x) { x_ = x; }
    int x() const { return x_; }

    void setY(int y) { y_ = y; }
    int y() const { return y_; }

    void setValue(double value) { value_ = value; }
    void setValue(QString value) { value_ = value; }
    const QVariant &value() const { return value_; }

    void addParent(Node *);
    void addChild(Node *);

    bool hasParents() const { return parents_.empty(); }
    int numParennts() const { return parents_.count(); }
    const Node *parent(int p) const { return parents_[p]; }
    Node *parent(int p) { return parents_[p]; }
    const QVector<Node *> parents() const { return parents_; }

    int maxChildren() const { return maxChildren_; }
    bool hasChildren() const { return !children_.empty(); }
    int numChildren() const { return children_.count(); }
    const Node *child(int c) const { return children_[c]; }
    Node *child(int c) { return children_[c]; }
    const QVector<Node *> children() const { return children_; }
    QVector<Node *> children() { return children_; }

    void readJson(const QJsonObject &);
    void writeJson(QJsonObject &) const;

    bool loadJson(const QString &);
    bool saveJson(const QString &) const;

    static void createTree(Node *);
    void layout();

private:

    const int maxParents_ = 1;
    const int maxChildren_ = 2;

    int x_;
    int y_;

    QString name_;
    QUuid id_;
    NodeType nodeType_;

    QVector<Node *> parents_;
    QVector<Node *> children_;
    QColor color_;
    QVariant value_;

    void layoutTraverse(Node *, int &, int &);
    void layoutVisit(Node *, int &, int &);
};
