#include "TreeWindow.h"

#include <QCloseEvent>

#include "Node.h"
#include "TreeWidget.h"

TreeWindow::TreeWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Node *root = new Node();
    root->setName("root");
    root->setNodeType(Node::NodeType::String);
    root->setValue("foobarbaz");

    if (false)
    {
        root->loadJson("load.json");
        root->saveJson("load_check.json");
    }
    else
    {
        Node::createTree(root);
        root->layout();
        root->saveJson("save.json");
    }

    tree_ = root;

    treeWidget_ = new TreeWidget(this);
    treeWidget_->setTree(tree_);
    setCentralWidget(treeWidget_);
}

TreeWindow::~TreeWindow()
{

}

void TreeWindow::closeEvent(QCloseEvent *e)
{
    tree_->saveJson("save_check.json");
    QWidget::closeEvent(e);
}
