#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opersPopupDialog.h"

#include <QHeaderView>
#include <QIcon>
#include <QLabel>
#include <QStandardItemModel>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_delegate(new OpersItemDelegate(this))
    , m_treeView(new QTreeView(this))
    , m_model(new OpersModel(this))
{
    ui->setupUi(this);

    if(m_db.init()) // set database path
    {
        connect(m_delegate, &OpersItemDelegate::editRow, this, &MainWindow::onEditRow);

        setCentralWidget(m_treeView);
        m_treeView->setMouseTracking(true);
        m_treeView->header()->setHidden(true);
        m_treeView->setSelectionMode(QAbstractItemView::NoSelection);
        m_treeView->setItemDelegate(m_delegate);
        m_treeView->setModel(m_model);

        QList<CountryOperators> countries = m_db.countries();

        for(auto &country : countries)
        {
            QObject *obj = new QObject(this);
            obj->setObjectName(country.name);
            obj->setProperty("code", country.codeMnc);
            obj->setProperty("mcc", country.mcc);

            QList<CountryOperators> operators = m_db.operatorsByMcc(country.mcc);

            for(auto &oper : operators)
            {
                QObject *item = new QObject(obj);
                item->setObjectName(oper.name);
                item->setProperty("mnc", oper.codeMnc);
                item->setProperty("mcc", country.mcc);
            }

            m_model->insetrItem(obj, QModelIndex());
        }

        const int buttonSize = 32;

        m_addButton = new QPushButton(QIcon(":/Icons/add.png"), "", this);
        m_addButton->setFixedSize(buttonSize, buttonSize);
        m_addButton->move(width() - buttonSize * 2, height() - buttonSize * 2);

        connect(m_addButton, &QPushButton::clicked, this, &MainWindow::onAddRow);
    }
    else
    {
        QLabel *label = new QLabel(QString("The page could not be approved. An error occurred with database:\n%1").arg(m_db.lastError()), this);
        setCentralWidget(label);
        label->setAlignment(Qt::AlignCenter);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onEditRow(const QModelIndex &index)
{
    if(!index.model()->data(index, Qt::DisplayRole).canConvert<QHash<QString, QString>>())
        return;

    QHash<QString, QString> data = index.model()->data(index, Qt::DisplayRole).value<QHash<QString, QString>>();

    OpersPopupDialog dialog(m_db, data);
    dialog.setWindowModality(Qt::ApplicationModal);
    dialog.setModal(true);

    if(dialog.exec() == QDialog::Accepted)
    {
        CountryOperators oper;
        oper.name = dialog.name();
        oper.mcc = dialog.mcc();
        oper.codeMnc = dialog.mnc();

        if(m_db.changeNameOperator(oper))
            m_model->updateOperatorName(index, oper.name);
    }
}

void MainWindow::onAddRow()
{
    OpersPopupDialog dialog(m_db, QHash<QString, QString>());
    dialog.setWindowModality(Qt::ApplicationModal);
    dialog.setModal(true);

    if(dialog.exec() == QDialog::Accepted)
    {
        CountryOperators oper;
        oper.name = dialog.name();
        oper.mcc = dialog.mcc();
        oper.codeMnc = dialog.mnc();

        if(m_db.addOperator(oper))
        {
            QObject *item = new QObject();
            item->setObjectName(oper.name);
            item->setProperty("mcc", oper.mcc);
            item->setProperty("mnc", oper.codeMnc);

            m_model->insetrItem(item);
        }
    }
}
