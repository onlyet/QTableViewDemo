#include "MainWindow.h"
#include <QDebug>
#include <QTableView>
#include "TableModel.h"
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include <QPushButton>
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_tableView = ui->tableView;
    TableModel *model = new TableModel;
    Delegate *delegate = new Delegate;

    m_tableView->setModel(model);

    // 注释好像没有不同
    m_tableView->setItemDelegate(delegate);

    HeaderViewPrivate* header = new HeaderViewPrivate(Qt::Horizontal);
    QStandardItemModel* headModel = new QStandardItemModel;
    QStringList strHeader;
    strHeader << QStringLiteral("序号") << QStringLiteral("考试机IP") << QStringLiteral("联网状态") << QStringLiteral("考试机版本") << QStringLiteral("操作");
    headModel->setHorizontalHeaderLabels(strHeader);
    header->setModel(headModel);


    m_tableView->setHorizontalHeader(header);

    //QAbstractItemModel * headModel = header->model();
    //headModel->setHeaderData(0, Qt::Horizontal, "序号");

    //m_tableView->horizontalHeader()->model()->setHeaderData(0, Qt::Horizontal, "序号");
    //bool b = headModel->setHeaderData(0, Qt::Horizontal, "序号");

    //m_tableView->horizontalHeader()->set


    connect(qobject_cast<HeaderViewPrivate *>(m_tableView->horizontalHeader()), &HeaderViewPrivate::checked, [&](bool ischecked) {
        if (ischecked) m_tableView->selectAll();
        else m_tableView->clearSelection();
    });
    QItemSelectionModel *selectionModel = m_tableView->selectionModel();
    connect(selectionModel, &QItemSelectionModel::selectionChanged, model, &TableModel::onItemSelected);


    //m_tableView->setSortingEnabled(true);
    // QHeaderView will automatically resize the section to fill the available space.The size cannot be changed by the user or programmatically.
    m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //m_tableView->horizontalHeader()->setSortIndicatorShown(true);
    //m_tableView->horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);
    //m_tableView->horizontalHeader()->setSectionsClickable(true);
    //connect(m_tableView->horizontalHeader(), &QHeaderView::sectionClicked, [](int index) {
    //    qDebug() << index;
    //});

    m_tableView->verticalHeader()->hide();

    //QMap<int, QVariant> m;
    //m.insert(Qt::EditRole, "hello");
    //model->setItemData(m_tableView->currentIndex(), m);

    for (int i = 0; i < 10; ++i)
    {
        QPushButton* btn = new QPushButton(QString("btn%1").arg(i));
        connect(btn, &QPushButton::clicked, []() {
            QMessageBox::information(nullptr, "tips", "i am btn!");
        });
        m_tableView->setIndexWidget(model->index(i, 4), btn);
    }

}
