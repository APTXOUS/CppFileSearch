#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->data=new FileList;
    ui->setupUi(this);
    ui->treeWidget->setHeaderLabel(tr("搜索结果（父向）")); //设置头的标题
    ui->treeWidget_2->setHeaderLabel(tr("搜索结果（子向）"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QStringList directory=QFileDialog::getOpenFileNames(NULL,"添加文件",".","*");
    if(directory.length()!=0)
    {
        ui->listWidget->addItems(directory);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->listWidget_2->clear();
    this->data->clear();
    for(int i=0;i<ui->listWidget->count();i++)
    {
       this->data->AddNode(ui->listWidget->item(i)->text().toStdString());
    }
    FileNode *p;
    p = this->data->head;
    while (p != NULL)
    {
        string temp;
        temp+=p->Filename;
        this->ui->listWidget_2->addItem(QString::fromStdString(temp));
        p=p->next;
    }
}

void MainWindow::on_listWidget_2_itemClicked(QListWidgetItem *item)
{
    this->ui->listWidget_3->clear();
    string temp=(item->text().toStdString());
    FileNode *p;
    p=this->data->Locate(temp);
    FatherFile *q;
    q=p->Info.next;
    while(q!=NULL)
    {
        ui->listWidget_3->addItem(QString::fromStdString(q->name));
        q=q->next;
    }
}
void MainWindow::start_dfs_father(QTreeWidgetItem * last,string node_name)
{
    FileNode *p;
    p=this->data->Locate(node_name);
    FatherNode *q;
    q = p->FatherNext;
    while(q!=NULL)
    {
        QTreeWidgetItem *imageItem1_1 = new QTreeWidgetItem(last,QStringList(QString::fromStdString(q->NodeName)));
        if(this->data->Locate(q->NodeName)!=NULL)
        {
            this->start_dfs_father(imageItem1_1,q->NodeName);
        }
        q=q->next;
    }
}

void MainWindow::start_dfs_child(QTreeWidgetItem * last,string node_name)
{
    FileNode *p;
    p=this->data->Locate(node_name);
    ChildNode *q;
    q = p->ChildNext;
    while(q!=NULL)
    {
        QTreeWidgetItem *imageItem1_1 = new QTreeWidgetItem(last,QStringList(QString::fromStdString(q->NodeName)));
        if(this->data->Locate(q->NodeName)!=NULL)
        {
            this->start_dfs_child(imageItem1_1,q->NodeName);
        }
        q=q->next;
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    this->data->StartSearch();
    ui->treeWidget_2->clear();
    ui->treeWidget->clear();
    FileNode *p;
    p=this->data->head;
    while(p!=NULL)
    {
        QTreeWidgetItem *imageItem1 = new QTreeWidgetItem(ui->treeWidget,QStringList(QString::fromStdString(p->Filename)));
        FatherNode *q;
        q = p->FatherNext;
        while (q != NULL)
        {
            QTreeWidgetItem *imageItem1_1 = new QTreeWidgetItem(imageItem1,QStringList(QString::fromStdString(q->NodeName)));
            if(this->data->Locate(q->NodeName)!=NULL)
            {
                this->start_dfs_father(imageItem1_1,q->NodeName);
            }
            q=q->next;
        }
        p=p->next;
    }

    p=this->data->head;
    while(p!=NULL)
    {
        QTreeWidgetItem *imageItem1 = new QTreeWidgetItem(ui->treeWidget_2,QStringList(QString::fromStdString(p->Filename)));
        ChildNode *q;
        q = p->ChildNext;
        while (q != NULL)
        {
            QTreeWidgetItem *imageItem1_1 = new QTreeWidgetItem(imageItem1,QStringList(QString::fromStdString(q->NodeName)));
            if(this->data->Locate(q->NodeName)!=NULL)
            {
                this->start_dfs_child(imageItem1_1,q->NodeName);
            }
            q=q->next;
        }
        p=p->next;
    }

}



void MainWindow::on_pushButton_3_clicked()
{
    ui->treeWidget->expandAll();
    ui->treeWidget_2->expandAll();
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    ;
}
