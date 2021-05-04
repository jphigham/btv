#pragma once
#include <QMainWindow>

#include <QPoint>
#include <QString>

class QAction;
class QCloseEvent;
class QContextMenuEvent;

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
    virtual void contextMenuEvent(QContextMenuEvent *) override;
private slots:
    void open();
    void create();
    void addString();
    void addDouble();
    bool save();
    bool saveAs();
    void close();
private:
    TreeWidget *treeWidget_;
    QString currentFile_;
    QPoint contextPos_;
    QAction *addStringAction_;
    QAction *addDoubleAction_;
    void createActions();
};
