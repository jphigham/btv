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

    if (true)
    {
        tree_->loadJson("load.json");
        tree_->saveJson("load_verify.json");
    }
    else
    {
        tree_->setName("root");
        tree_->setNodeType(Node::NodeType::String);
        tree_->setValue("foobarbaz");
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
    tree_->saveJson("save_verify.json");
    QWidget::closeEvent(e);
}
