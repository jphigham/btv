#pragma once
#include <QMainWindow>

#include <QString>

class QCloseEvent;

class Node;
class TreeWidget;

class TreeWindow : public QMainWindow
{
public:
    TreeWindow(QWidget * = nullptr);
    virtual ~TreeWindow();
    bool loadFile(const QString &);
    bool saveFile(const QString &) const;
    static Node *createTree();
protected:
    virtual void closeEvent(QCloseEvent *) override;
private slots:
    void open();
    void create();
    bool save();
    bool saveAs();
    void close();
private:
    TreeWidget *treeWidget_;
    QString currentFile_;
    void createActions();
};
