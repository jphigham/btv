#include <QApplication>

#include <QFile>
#include <QJsonDocument>
#include <QMainWindow>

#include "Node.h"

void createTree(Node *parent)
{
    Node *l1 = new Node(parent);
    l1->setName("l1");
    l1->setNodeType(Node::NodeType::Float);
    l1->setValue(1.234);

    Node *r1 = new Node(parent);
    r1->setName("r1");
    r1->setNodeType(Node::NodeType::Float);
    r1->setValue(4.321);

    Node *ll1 = new Node(l1);
    ll1->setName("ll1");
    ll1->setNodeType(Node::NodeType::String);
    ll1->setValue("foo");

    Node *rl1 = new Node(l1);
    rl1->setName("rl1");
    rl1->setNodeType(Node::NodeType::String);
    rl1->setValue("bar");

    Node *rrl1 = new Node(rl1);
    rrl1->setName("rrl1");
    rrl1->setNodeType(Node::NodeType::String);
    rrl1->setValue("baz");
}

void visit(Node *t, int &x, int &y)
{
    t->setX(++x);
    t->setY(y);
}

void traverse(Node *t, int &x, int &y)
{
    y++;

    if (t->numChildren() > 0)
        traverse(t->child(0), x, y);
    visit(t, x, y);
    if (t->numChildren() > 1)
        traverse(t->child(1), x, y);

    y--;
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
    QStringList args = QApplication::arguments();

    bool load = false;

    Node *root = new Node();
    root->setName("root");
    root->setNodeType(Node::NodeType::String);
    root->setValue("foobarbaz");

    if (load)
    {
        QFile loadFile("load.json");
        loadFile.open(QIODevice::ReadOnly);
        QByteArray loadData = loadFile.readAll();
        QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
        root->readJson(loadDoc.object());
        loadFile.close();
    }
    else
    {
        createTree(root);
        int x(0), y(0);
        traverse(root, x, y);
        QJsonObject treeObject;
        root->writeJson(treeObject);
        QFile saveFile("save.json");
        saveFile.open(QIODevice::WriteOnly);
        saveFile.write(QJsonDocument(treeObject).toJson());
        saveFile.close();
    }

    QMainWindow w;
	w.show();
	return app.exec();
}
