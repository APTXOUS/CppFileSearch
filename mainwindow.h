#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fileinfo.h"
#include "filesearch.h"
#include<QDir>
#include<QFile>
#include<QFileDialog>
#include<qlistwidget.h>
#include<qtreewidget.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    FileList *data;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_listWidget_2_itemClicked(QListWidgetItem *item);

    void on_pushButton_4_clicked();

    void start_dfs_father(QTreeWidgetItem * ,string);

    void start_dfs_child(QTreeWidgetItem * ,string);

    void on_pushButton_3_clicked();

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
