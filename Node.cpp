#include "Node.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

Node::Node(Node *parent)
    : x_(-1), y_(-1),
      id_(QUuid::createUuid())
{
    addParent(parent);
    if (parent != nullptr)
        parent->addChild(this);
}

Node::~Node()
{
    for (auto child : children_) {
        delete child;
    }
    children_.clear();
    for (auto parent : parents_) {
        parent->children().remove(parent->children().indexOf(this));
    }
}

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

    if (json.contains("nodetype") && json["nodetype"].isDouble())
        setNodeType(static_cast<NodeType>(json["nodetype"].toInt()));

    if (json.contains("x") && json["x"].isDouble())
        setX(json["x"].toInt());

    if (json.contains("y") && json["y"].isDouble())
        setY(json["y"].toInt());

    if (json.contains("nodetype") && json["nodetype"].isDouble()
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

bool Node::loadJson(const QString &filename)
{
    QFile loadFile(filename);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open json load file.");
        return false;
    }
    QByteArray loadData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
    readJson(loadDoc.object());
    loadFile.close();
    return true;
}

bool Node::saveJson(const QString &filename) const
{
    QJsonObject treeObject;
    writeJson(treeObject);
    QFile saveFile(filename);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open json save file.");
        return false;
    }
    saveFile.write(QJsonDocument(treeObject).toJson());
    saveFile.close();
    return true;
}

void Node::layout()
{
    int x(-1), y(-1);
    layoutTraverse(this, x, y);
}

void Node::layoutTraverse(Node *n, int &x, int &y)
{
    y++;

    int mid = n->numChildren() / 2;
    for (int l = 0; l < mid; l++)
        layoutTraverse(n->child(l), x, y);
    layoutVisit(n, x, y);
    for (int r = mid; r < n->numChildren(); r++)
        layoutTraverse(n->child(r), x, y);

    y--;
}

void Node::layoutVisit(Node *n, int &x, int &y)
{
    n->setX(++x);
    n->setY(y);
}

void Node::createTree(Node *parent)
{
    Node *A1 = new Node(parent);
    A1->setName("A1");
    A1->setNodeType(Node::NodeType::Float);
    A1->setValue(4.57);

    Node *A2 = new Node(A1);
    A2->setName("A2");
    A2->setNodeType(Node::NodeType::String);
    A2->setValue("foo");

    Node *B2 = new Node(A1);
    B2->setName("B2");
    B2->setNodeType(Node::NodeType::String);
    B2->setValue("bar");

    Node *B1 = new Node(parent);
    B1->setName("B1");
    B1->setNodeType(Node::NodeType::Float);
    B1->setValue(-8.2);

    Node *C2 = new Node(B1);
    C2->setName("C2");
    C2->setNodeType(Node::NodeType::Float);
    C2->setValue(2.2);

    Node *A3 = new Node(B2);
    A3->setName("A3");
    A3->setNodeType(Node::NodeType::String);
    A3->setValue("baz");

    Node *B3 = new Node(C2);
    B3->setName("B3");
    B3->setNodeType(Node::NodeType::String);
    B3->setValue("centerfield");

    Node *C3 = new Node(C2);
    C3->setName("C3");
    C3->setNodeType(Node::NodeType::String);
    C3->setValue("rightfield");

    Node *A4 = new Node(B3);
    A4->setName("A4");
    A4->setNodeType(Node::NodeType::String);
    A4->setValue("dungeon");
}
