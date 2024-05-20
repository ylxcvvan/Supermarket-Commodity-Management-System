#include "widgetcashiermanager.h"
#include "controller/database/sqlcommondity.h"
#include "controller/database/sqlinventory.h"
#include "ui_widgetcashiermanager.h"

WidgetCashierManager::WidgetCashierManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetCashierManager)
    ,p_GoodsListService(new GoodsTableService)
    ,p_ComItemService(new ComItemTableService)
    ,goodsTableRow(0)
    ,totalPrice(0)
    ,totalCount(0)
{
    ui->setupUi(this);

    // 创建 QTableView
    ui->tableView->setModel(p_GoodsListService->getGTable());
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //设置右侧所有的tableview


    findAllTableViews(this, viewList);

    std::sort(viewList.begin(), viewList.end(), [](const QTableView *a, const QTableView *b) {
        // 比较两个QTableView的对象名
        return a->objectName() < b->objectName();
    });

    loadModel();
    //将tableview的数量改变的信号与updateTotalPrice_TotalCounts（）函数连接；

    connect(p_GoodsListService->getGTable(),&QAbstractTableModel::dataChanged,this,&WidgetCashierManager::updateTotalPrice_TotalCounts);

    for(int i=0;i<viewList.size();++i)
    {
        auto &view=viewList[i];
        qDebug()<<"view I="<<i<<"name:"<<view->objectName();
        view->setModel(p_ComItemService->getTable(i));
        view->setItemDelegate(p_ComItemService->getComItemDelegate());
        view->horizontalHeader()->setVisible(false); // 隐藏水平表头
        view->verticalHeader()->setVisible(false);   // 隐藏垂直表头
        view->setShowGrid(false);                    // 隐藏网格线
        view->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        view->resizeColumnsToContents();
        view->resizeRowsToContents();
        //连接槽函数
        connect(view,&QTableView::doubleClicked,this,[this](const QModelIndex &index)
                {this->getCommodityinRightTableView(index);
        });
    }
    // 表格视图设置



}

WidgetCashierManager::~WidgetCashierManager()
{
    delete p_GoodsListService;
    delete ui;
}

void WidgetCashierManager::loadModel()
{
    for(int i=0;i<ui->tabWidget->count();++i)
    {
        QString category=ui->tabWidget->tabText(i);
        p_ComItemService->setComItemList(i,SqlCommondityItem::Query(-1,"","",category));
    }
}

void WidgetCashierManager::findAllTableViews(QObject *parent, QVector<QTableView *> &viewList)
{
    const QObjectList &children = parent->children();
    for (QObject *child : children) {
        // 打印组件对象名
        QString str = child->objectName();
        qDebug() << str;

        // 判断组件对象名是否以"tableView_"为前缀
        if (str.startsWith("tableView_")) {
            qDebug() << str << "add";
            QTableView *view = qobject_cast<QTableView*>(child);
            if (view) {
                viewList.push_back(view);
            }
        }

        // 递归查找子组件
        findAllTableViews(child, viewList);
    }
}

void WidgetCashierManager::updateTotalPrice_TotalCounts()
{
    auto glist = p_GoodsListService->getGTable()->getGoodsList();
    totalPrice = 0;
    totalCount = 0;
    for(auto i : glist){
        totalPrice += i.back().toDouble();
        totalCount += i.at(4).toDouble();
    }
    ui->labelTotalPrice->setText(tr("%1").arg(totalPrice));
    ui->labelTotalAmount->setText(tr("%1").arg(totalCount));
}

void WidgetCashierManager::getCommodityinRightTableView(const QModelIndex &index)
{
    //修复了双击空白数组导致的程序崩溃问题
    if(!index.data().isValid())
        return;

    int itemid=p_ComItemService->getTable(ui->tabWidget->currentIndex())->getCListId(index);
    ui->comboBox->clear();
    comList=SqlCommondity::Query(-1,itemid);
    for(auto &com:comList)
    {
        ui->comboBox->addItem((tr("名称：%1 价格：%2元 过期时间：%3 ").arg(com.getName()).arg(com.getPrice()).arg(com.getSellByTime().toString("yyyy-MM-dd"))));
    }
}

void WidgetCashierManager::on_lineEditCommodityId_textChanged(const QString &arg1)
{
    ui->comboBox->clear();
    comList = SqlCommondity::Query(arg1.toInt());
    for(auto &com:comList)
    {
        ui->comboBox->addItem((tr("名称：%1 价格：%2元  过期时间：%3 ").arg(com.getName()).arg(com.getPrice()).arg(com.getSellByTime().toString("yyyy-ddMM-dd"))));
    }
}


void WidgetCashierManager::on_pushButtonAdd_clicked()
{
    if(!ui->comboBox->count())
        return;

    int cid = comList[ui->comboBox->currentIndex()].getId();
    qDebug()<<cid;
    auto query = SqlCommondity::Query(cid);
    if(!query.size())
        return;


    auto item =query.front();
    double amount = ui->spinBoxAmount->value();
    double price = amount * item.getPrice();
    QVector<QVector<QVariant>>lists{
                                     {item.getId(),item.getName(),item.getSellByTime(),item.getPrice(),
                                      amount,price}
                                    };

    p_GoodsListService->getGTable()->insertRows(goodsTableRow++,1,lists);


    updateTotalPrice_TotalCounts();
}

