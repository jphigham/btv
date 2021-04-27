#include "Node.h"

#include <QJsonArray>

Node::Node(Node *parent)
    : x_(-1), y_(-1),
      id_(QUuid::createUuid())
{
    addParent(parent);
    if (parent != nullptr)
        parent->addChild(this);
}

Node::~Node() {}

void Node::addParent(Node *parent)
{
    if (parent != nullptr
            && parents_.size() < maxParents_
            && ! parents_.contains(parent)) {
        parents_.append(parent);
    }
}

void Node::addChild(Node *child)
{
    if (children_.size() < maxChildren_ && ! children_.contains(child)) {
        children_.append(child);
    }
}

void Node::readJson(const QJsonObject &json)
{
    if (json.contains("name") && json["name"].isString())
        setName(json["name"].toString());

    if (json.contains("id") && json["id"].isString())
        setId(json["id"].toString());

    if (json.contains("nodetype") && json["nodetype"].isString())
        setNodeType(static_cast<NodeType>(json["nodetype"].toInt()));

    if (json.contains("x") && json["x"].isString())
        setX(json["x"].toInt());

    if (json.contains("y") && json["y"].isString())
        setY(json["y"].toInt());

    if (json.contains("nodetype") && json["nodetype"].isString()
            && json.contains("value")) {
        setNodeType(static_cast<NodeType>(json["nodetype"].toInt()));
        switch (nodeType_) {
        case NodeType::Float:
            value_ = QVariant(json["value"].toDouble(0.0));
            break;
        case NodeType::String:
            value_ = QVariant(json["value"].toString(""));
            break;
        default:
            qWarning("Unknown node type");
        }
    }

    if (json.contains("children") && json["children"].isArray()) {
        QJsonArray childArray = json["children"].toArray();
        children_.clear();
        children_.reserve(childArray.size());
        for (int c = 0; c < childArray.size(); c++ ) {
            QJsonObject childObject = childArray[c].toObject();
            Node *child = new Node(this);
            child->readJson(childObject);
        }
    }
}

void Node::writeJson(QJsonObject &json) const
{
    json["name"] = name_;
    json["id"] = id_.toString();
    json["nodetype"] = nodeType_;
    json["x"] = x_;
    json["y"] = y_;
    json["value"] = value_.toString();

    QJsonArray childArray;
    for (const Node *child : children_) {
        QJsonObject childObject;
        child->writeJson(childObject);
        childArray.append(childObject);
    }
    json["children"] = childArray;
}

void Node::layout()
{
    int x(0), y(0);
    layout_traverse(this, x, y);
}

void Node::layout_traverse(Node *n, int &x, int &y)
{
    y++;

    int mid = n->numChildren() / 2;
    for (int l = 0; l < mid; l++)
        layout_traverse(n->child(l), x, y);
    layout_visit(n, x, y);
    for (int r = mid; r < n->numChildren(); r++)
        layout_traverse(n->child(r), x, y);

    y--;
}

void Node::layout_visit(Node *t, int &x, int &y)
{
    t->setX(++x);
    t->setY(y);
}
