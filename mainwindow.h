#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTreeView>

#include "dbWorker.h"
#include "opersModel.h"
#include "opersItemDelegate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onEditRow(const QModelIndex &index);
    void onAddRow();

private:
    Ui::MainWindow      *ui;
    OpersItemDelegate   *m_delegate;
    QTreeView           *m_treeView;
    OpersModel          *m_model;
    QPushButton         *m_addButton;
    DBWorker            m_db;
};
#endif // MAINWINDOW_H
