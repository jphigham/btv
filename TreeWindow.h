#pragma once
#include <QMainWindow>

class QCloseEvent;

class Node;
class TreeWidget;

class TreeWindow : public QMainWindow
{
public:
    TreeWindow(QWidget * = nullptr);
    virtual ~TreeWindow();
protected:
    virtual void closeEvent(QCloseEvent *) override;
private:
    TreeWidget *treeWidget_;
    Node *tree_;
};
