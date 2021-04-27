#include "TreeWindow.h"

#include <QCloseEvent>
#include <QScrollArea>
#include <QVBoxLayout>

#include "Node.h"
#include "TreeWidget.h"

TreeWindow::TreeWindow(QWidget *parent)
    : QMainWindow(parent)
{
    tree_ = new Node();
    tree_->setName("root");
    tree_->setNodeType(Node::NodeType::String);
    tree_->setValue("foobarbaz");

    if (false)
    {
        tree_->loadJson("load.json");
        tree_->saveJson("load_check.json");
    }
    else
    {
        Node::createTree(tree_);
        tree_->layout();
        tree_->saveJson("save.json");
    }

    QScrollArea *scrollArea = new QScrollArea;
    treeWidget_ = new TreeWidget;
    treeWidget_->setTree(tree_);
    scrollArea->setWidget(treeWidget_);

    QWidget *centralWidget = new QWidget;
    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addWidget(scrollArea, 1);
    centralWidget->setLayout(centralLayout);
    setCentralWidget(centralWidget);
}

TreeWindow::~TreeWindow()
{

}

void TreeWindow::closeEvent(QCloseEvent *e)
{
    tree_->saveJson("save_check.json");
    QWidget::closeEvent(e);
}
