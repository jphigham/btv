#include "TreeWindow.h"

#include <QAction>
#include <QCloseEvent>
#include <QCoreApplication>
#include <QFileDialog>
#include <QScrollArea>
#include <QVBoxLayout>

#include <memory>

#include "Node.h"
#include "TreeWidget.h"

TreeWindow::TreeWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("btv");

    QScrollArea *scrollArea = new QScrollArea;
    treeWidget_ = new TreeWidget;
    scrollArea->setWidget(treeWidget_);

    QWidget *centralWidget = new QWidget;
    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addWidget(scrollArea, 1);
    centralWidget->setLayout(centralLayout);
    setCentralWidget(centralWidget);

    createActions();
}

TreeWindow::~TreeWindow()
{

}

void TreeWindow::open()
{
	if (!currentFile_.isEmpty())
		close();
    QString openFileName = QFileDialog::getOpenFileName(this, "Open tree file", "", "*.json");
    if (!openFileName.isEmpty())
        loadFile(openFileName);
}

void TreeWindow::create()
{
    treeWidget_->setTree(TreeWindow::createTree());
    treeWidget_->update();
}

bool TreeWindow::save()
{
    if (currentFile_.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(currentFile_);
    }
}

bool TreeWindow::saveAs()
{
#if 1
    QString saveFileName = QFileDialog::getSaveFileName(this, "Save tree file", "", "*.json");
    if (saveFileName.isEmpty())
    	return false;
    currentFile_ = saveFileName;
#else
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() != QDialog::Accepted)
        return false;
    currentFile_ = dialog.selectedFiles().first();
#endif
    setWindowTitle("btv - " + currentFile_);
    return saveFile(currentFile_);
}

void TreeWindow::close()
{
    treeWidget_->close();
    currentFile_ = "";
    setWindowTitle("btv");
}

void TreeWindow::createActions()
{
    QAction *openAction = new QAction("&Open", this);
    openAction->setShortcuts(QKeySequence::Open);
    connect(openAction, &QAction::triggered, this, &TreeWindow::open);
    addAction(openAction);

    QAction *createAction = new QAction("&Create", this);
    connect(createAction, &QAction::triggered, this, &TreeWindow::create);
    addAction(createAction);

    QAction *saveAction = new QAction("&Save", this);
    saveAction->setShortcuts(QKeySequence::Save);
    connect(saveAction, &QAction::triggered, this, &TreeWindow::save);
    addAction(saveAction);

    QAction *saveAsAction = new QAction("Save &As", this);
    saveAsAction->setShortcuts(QKeySequence::SaveAs);
    connect(saveAsAction, &QAction::triggered, this, &TreeWindow::saveAs);
    addAction(saveAsAction);

    QAction *closeAction = new QAction("&Close", this);
    closeAction->setShortcuts(QKeySequence::Close);
    connect(closeAction, &QAction::triggered, this, &TreeWindow::close);
    addAction(closeAction);

    QAction *quitAction = new QAction("E&xit", this);
    quitAction->setShortcuts(QKeySequence::Quit);
    connect(quitAction, &QAction::triggered, this, &QCoreApplication::quit);
    addAction(quitAction);

    setContextMenuPolicy(Qt::ActionsContextMenu);
}

bool TreeWindow::loadFile(const QString &filename)
{
    Node *tree = new Node();
    if (tree->loadJson(filename)) {
        treeWidget_->setTree(tree);
        treeWidget_->update();
        setWindowTitle(QString("btv - %1").arg(filename));
        currentFile_ = filename;
        return true;
    } else {
    	delete tree;
        return false;
    }
}

bool TreeWindow::saveFile(const QString &filename) const
{
    if (treeWidget_ != nullptr && treeWidget_->tree()) {
        return treeWidget_->tree()->saveJson(filename);
    } else {
        qWarning("No tree to save");
        return false;
    }
}

Node *TreeWindow::createTree()
{
    Node *root = new Node();
    root->setName("root");
    root->setNodeType(Node::NodeType::String);
    root->setValue("root");
    Node::createTree(root);
    root->layout();
    return root;
}

void TreeWindow::closeEvent(QCloseEvent *e)
{
    QWidget::closeEvent(e);
}
