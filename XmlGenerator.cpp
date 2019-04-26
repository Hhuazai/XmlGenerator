#include "XmlGenerator.h"
#include "ui_xmlgenerator.h"

#include <QDebug>
#include <QDomText>
#include <QDomElement>
#include <QFileDialog>
#include <QMessageBox>

XmlGenerator::XmlGenerator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::XmlGenerator)
{
    ui->setupUi(this);

    InitUi();

    rootItem = new QTreeWidgetItem;

    connect(ui->treeWidget, &QTreeWidget::currentItemChanged, this, &XmlGenerator::CurrentItemChangedSlot);
}

XmlGenerator::~XmlGenerator()
{
    delete ui;
}

void XmlGenerator::InitUi()
{
    /*如果采用设置样式表的方式给按钮添加图片，则按钮的形态会消失，比如，按钮没有边框
    ui->btn_addItem->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/image/添加1.png);}"
                                "QPushButton:hover{border-image: url(:/new/prefix1/image/添加2.png);}");
    ui->btn_addChildItem->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/image/添加子项1.png);}"
                                 "QPushButton:hover{border-image: url(:/new/prefix1/image/添加子项2.png);}");
    ui->btn_delItem->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/image/减号1.png);}"
                                "QPushButton:hover{border-image: url(:/new/prefix1/image/减号2.png);}");
    ui->btn_up->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/image/上1.png);}"
                                 "QPushButton:hover{border-image: url(:/new/prefix1/image/上2.png);}");
    ui->btn_down->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/image/下1.png);}"
                                "QPushButton:hover{border-image: url(:/new/prefix1/image/下2.png);}");
    ui->btn_changeToFather->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/image/左上1.png);}"
                                 "QPushButton:hover{border-image: url(:/new/prefix1/image/左上2.png);}");
    ui->btn_changeToChild->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/image/下右1.png);}"
                                 "QPushButton:hover{border-image: url(:/new/prefix1/image/下右2.png);}");*/

    ui->btn_addItem->setIcon(QIcon(":/new/prefix1/image/加号2.png"));
    ui->btn_addChildItem->setIcon(QIcon(":/new/prefix1/image/添加子项1.png"));
    ui->btn_delItem->setIcon(QIcon(":/new/prefix1/image/减号1.png"));
    ui->btn_up->setIcon(QIcon(":/new/prefix1/image/上1.png"));
    ui->btn_down->setIcon(QIcon(":/new/prefix1/image/下1.png"));
    ui->btn_changeToFather->setIcon(QIcon(":/new/prefix1/image/左上1.png"));
    ui->btn_changeToChild->setIcon(QIcon(":/new/prefix1/image/下右1.png"));

    ui->btn_addItem->setStatusTip(QStringLiteral("新建项目"));
    ui->btn_addChildItem->setStatusTip(QStringLiteral("新建子项目"));
    ui->btn_delItem->setStatusTip(QStringLiteral("删除项目"));
    ui->btn_up->setStatusTip(QStringLiteral("向上移动项目"));
    ui->btn_down->setStatusTip(QStringLiteral("向下移动项目"));
    ui->btn_changeToFather->setStatusTip(QStringLiteral("向左移动项目(移动到父项目之前)"));
    ui->btn_changeToChild->setStatusTip(QStringLiteral("向右移动项目(作为下一个同级项目的第一个子项目)"));

    //ui->btn_addItem->setWhatsThis(QStringLiteral("新建项目"));

    ui->btn_addItem->setEnabled(true);
    ui->btn_addChildItem->setEnabled(false);
    ui->btn_delItem->setEnabled(false);
    ui->btn_up->setEnabled(false);
    ui->btn_down->setEnabled(false);
    ui->btn_changeToFather->setEnabled(false);
    ui->btn_changeToChild->setEnabled(false);

    //给下面这些控件(都是按钮)安装事件过滤器
    ui->btn_addItem->installEventFilter(this);
    ui->btn_addChildItem->installEventFilter(this);
    ui->btn_delItem->installEventFilter(this);
    ui->btn_up->installEventFilter(this);
    ui->btn_down->installEventFilter(this);
    ui->btn_changeToFather->installEventFilter(this);
    ui->btn_changeToChild->installEventFilter(this);
}

//该函数相当于创建事件过滤器
//在目标对象(obj)接收到事件之前,该函数被调用。
//也就是说，如果在该函数中停止了某个事件，那么目标对象以及以后所有的事件过滤器根本不会知道这么一个事件。
bool XmlGenerator::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->btn_addItem
            || obj == ui->btn_addChildItem
            || obj == ui->btn_delItem
            || obj == ui->btn_up
            || obj == ui->btn_down
            || obj == ui->btn_changeToFather
            || obj == ui->btn_changeToChild)
    {
        if (event->type() == QEvent::EnabledChange)
        {
            //这些资源图片的格式：2为高亮的图片，表示按钮可用；1为灰色图片，表示按钮不可用
            ui->btn_addItem->setIcon(QIcon(QString(":/new/prefix1/image/加号%1.png").arg((ui->btn_addItem->isEnabled()) ? 2 : 1)));
            ui->btn_addChildItem->setIcon(QIcon(QString(":/new/prefix1/image/添加子项%1.png").arg((ui->btn_addChildItem->isEnabled()) ? 2 : 1)));
            ui->btn_delItem->setIcon(QIcon(QString(":/new/prefix1/image/减号%1.png").arg((ui->btn_delItem->isEnabled()) ? 2 : 1)));
            ui->btn_up->setIcon(QIcon(QString(":/new/prefix1/image/上%1.png").arg((ui->btn_up->isEnabled()) ? 2 : 1)));
            ui->btn_down->setIcon(QIcon(QString(":/new/prefix1/image/下%1.png").arg((ui->btn_down->isEnabled()) ? 2 : 1)));
            ui->btn_changeToFather->setIcon(QIcon(QString(":/new/prefix1/image/左上%1.png").arg((ui->btn_changeToFather->isEnabled()) ? 2 : 1)));
            ui->btn_changeToChild->setIcon(QIcon(QString(":/new/prefix1/image/下右%1.png").arg((ui->btn_changeToChild->isEnabled()) ? 2 : 1)));

            return true;    //返回true表示我们已经处理了事件，不用再转发该事件（表示我们关心该事件）
        }
        else
        {
            return false;    //如果是其它类型的事件，接续转发事件（表示我们不关心）
        }
    }
    else    //如果不是这些控件
    {
        return QMainWindow::eventFilter(obj, event);    //对于其它的组件，我们并不保证是不是还有过滤器，于是最保险的办法是调用父类的函数
    }
}

//注意这里的槽函数参数比信号的参数少，信号是void currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
void XmlGenerator::CurrentItemChangedSlot(QTreeWidgetItem *current)
{
    if (current->parent() != NULL)
    {
        QTreeWidgetItem *curFather = current->parent();
        int siblings = curFather->childCount();         //判断当前节点是否存在兄弟姐妹
        int index = curFather->indexOfChild(current);   //判断当前节点在家庭成员中的位置

        ui->btn_addChildItem->setEnabled(true);
        ui->btn_delItem->setEnabled(true);

        /*if (curFather->parent() != NULL)  //若爷爷节点存在，则有可能与父节点同级
        {
            ui->btn_changeToFather->setEnabled(true);
        }
        else
        {
            ui->btn_changeToFather->setEnabled(false);
        }*/

        //这种写法使代码更加简洁
        ui->btn_changeToFather->setEnabled(curFather->parent());

        if (siblings <= 1)  //独生子，也就不需要排名了
        {
            ui->btn_up->setEnabled(false);
            ui->btn_down->setEnabled(false);
            //ui->btn_changeToChild->setEnabled(false);
        }
        else
        {
            if (0 == index) //家中排行老大，肯定有弟弟，地位只能下降
            {
                ui->btn_up->setEnabled(false);
                ui->btn_down->setEnabled(true);
                //ui->btn_changeToChild->setEnabled(true);
            }
            else if (index == (siblings - 1))   //家中排行老末，肯定没有弟弟，地位只能上升
            {
                ui->btn_up->setEnabled(true);
                ui->btn_down->setEnabled(false);
                //ui->btn_changeToChild->setEnabled(false);
            }
            else    //家中排行在中间，肯定有弟弟，地位可升可降
            {
                ui->btn_up->setEnabled(true);
                ui->btn_down->setEnabled(true);
                //ui->btn_changeToChild->setEnabled(true);
            }
        }
        //我们发现，btn_changeToChild与btn_down始终一致，因为只要有弟弟，弟节点就有可能成为哥哥节点，也有可能成为父节点，你说气人不气人
        ui->btn_changeToChild->setEnabled(ui->btn_down->isEnabled());
    }
    else
    {
        ui->btn_delItem->setEnabled(false);
    }
}

//添加项目
void XmlGenerator::on_btn_addItem_clicked()
{
    if (rootItem->text(0) == "")
    {
        rootItem->setText(0, QStringLiteral("新建列"));
        rootItem->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        ui->treeWidget->addTopLevelItem(rootItem);
        ui->treeWidget->setCurrentItem(rootItem, 0, QItemSelectionModel::ClearAndSelect);
        ui->btn_addChildItem->setEnabled(true);
    }
    if (ui->treeWidget->currentItem()->parent() != NULL)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget->currentItem()->parent());
        item->setText(0, QStringLiteral("新建项目"));
        item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        ui->treeWidget->setCurrentItem(item, 0, QItemSelectionModel::ClearAndSelect);
    }
}

//添加子项目
void XmlGenerator::on_btn_addChildItem_clicked()
{
    QTreeWidgetItem *child = new QTreeWidgetItem(ui->treeWidget->currentItem());
    child->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | /*Qt::ItemIsUserCheckable | */Qt::ItemIsSelectable);
    child->setText(0, QStringLiteral("新建子项目"));
    ui->treeWidget->setCurrentItem(child, 0, QItemSelectionModel::ClearAndSelect);
    ui->treeWidget->expandItem(ui->treeWidget->currentItem()->parent());
}

//移除项目 若存在子项目，连同子项目一起移除
void XmlGenerator::on_btn_delItem_clicked()
{
    if (ui->treeWidget->currentItem() != rootItem)
    {
        ui->treeWidget->currentItem()->parent()->removeChild(ui->treeWidget->currentItem());
    }
}

//成为你哥
void XmlGenerator::on_btn_up_clicked()
{
    //先找到你哥
    QTreeWidgetItem *curFather = ui->treeWidget->currentItem()->parent();
    int curIndex = curFather->indexOfChild(ui->treeWidget->currentItem());
    QTreeWidgetItem *olderItem = curFather->child(curIndex - 1);

    //移除你哥
    QTreeWidgetItem *tmpItem = olderItem;
    curFather->removeChild(olderItem);

    //添加你弟
    curFather->insertChild(curIndex, tmpItem);

    //虽然位置变了，但主角还是我
    ui->treeWidget->setCurrentItem(ui->treeWidget->currentItem(), 0, QItemSelectionModel::ClearAndSelect);

    ui->treeWidget->expandItem(tmpItem);

    //这里为什么要手动发送这个信号？
    //原因是：currentItemChanged信号是QTreeWidget的信号，如果当前节点改变了，该信号就会被发出。
    //但是在这种情况，当前节点(ui->treeWidget->currentItem())并没有改变，而只是位置改变了，当前节点向上移动了一次，而且依旧是被选中的状态
    //所以，这里的移动实际上并未改变当前节点，该信号也就发送不了，所以我们需要人工发射这个信号
    emit ui->treeWidget->currentItemChanged(ui->treeWidget->currentItem(), ui->treeWidget->currentItem());
}

//成为你弟
void XmlGenerator::on_btn_down_clicked()
{
    //先找到你弟
    QTreeWidgetItem *curFather = ui->treeWidget->currentItem()->parent();
    int curIndex = curFather->indexOfChild(ui->treeWidget->currentItem());
    //QTreeWidgetItem *youngerItem = curFather->child(curIndex + 1);

    //移除你自己
    QTreeWidgetItem *tmpItem = ui->treeWidget->currentItem();
    curFather->removeChild(ui->treeWidget->currentItem());

    //添加你自己
    curFather->insertChild(curIndex + 1, tmpItem);

    //虽然位置变了，但主角还是我
    ui->treeWidget->setCurrentItem(tmpItem, 0, QItemSelectionModel::ClearAndSelect);

    emit ui->treeWidget->currentItemChanged(tmpItem, tmpItem);
}

//成为你爸爸的哥哥
void XmlGenerator::on_btn_changeToFather_clicked()
{
    //先找到你爸爸
    QTreeWidgetItem *curFather = ui->treeWidget->currentItem()->parent();

    //再找你爷爷
    QTreeWidgetItem *curGrandpa = curFather->parent();

    //看你爸在家中排行
    int faIndex = curGrandpa->indexOfChild(curFather);

    //让你爸移除你
    QTreeWidgetItem *tmpItem = ui->treeWidget->currentItem();
    curFather->removeChild(ui->treeWidget->currentItem());

    //你爷爷把你放到你爸的位置，你爸的位置往后挪
    curGrandpa->insertChild(faIndex, tmpItem);

    //行了行了，没有忘，主角还是你
    ui->treeWidget->setCurrentItem(tmpItem, 0, QItemSelectionModel::ClearAndSelect);
}

//成为你弟的第一个崽
void XmlGenerator::on_btn_changeToChild_clicked()
{
    //先明确自己在家中的排行
    QTreeWidgetItem *curFather = ui->treeWidget->currentItem()->parent();
    int curIndex = curFather->indexOfChild(ui->treeWidget->currentItem());

    //找你弟
    QTreeWidgetItem *youngerItem = curFather->child(curIndex + 1);

    //让你爸移除你
    QTreeWidgetItem *tmpItem = ui->treeWidget->currentItem();
    curFather->removeChild(ui->treeWidget->currentItem());

    //让你添加你为第一个崽,很不幸
    youngerItem->insertChild(0, tmpItem);

    //幸运的是,你依然是主角
    ui->treeWidget->setCurrentItem(tmpItem, 0, QItemSelectionModel::ClearAndSelect);
}

bool XmlGenerator::GenerateXML()
{
    doc.clear();
    QString strHeader( "version=\"1.0\" encoding=\"UTF-8\"" );
    doc.appendChild(doc.createProcessingInstruction("xml", strHeader) );
    QDomElement	rootElement = doc.createElement(QStringLiteral("国家"));
    rootElement.setAttribute( " name ", rootItem->text(0));
    doc.appendChild( rootElement );

    QDomElement provincesElement;
    QDomElement cityElement;
    QDomElement districtElement;

//    QDomText provincesText;
//    QDomText cityText;
    QDomText districtText;

    for (int i = 0; i < rootItem->childCount(); i++)
    {
        provincesElement = doc.createElement(QStringLiteral("省"));
//        provincesText = doc.createTextNode(rootItem->child(i)->text(0));
//        provincesElement.appendChild(provincesText);
        provincesElement.setAttribute( "name", rootItem->child(i)->text(0));
        rootElement.appendChild(provincesElement);

        for (int j = 0; j < rootItem->child(i)->childCount(); j++)
        {
            if (rootItem->child(i)->child(j)->childCount() < 0)
            {
                return false;
            }
            cityElement = doc.createElement(QStringLiteral("市"));
//            cityText = doc.createTextNode(rootItem->child(i)->child(j)->text(0));
//            cityElement.appendChild(cityText);
//            cityElement.setAttribute( "name", "City");
            cityElement.setAttribute( "name", rootItem->child(i)->child(j)->text(0));
            provincesElement.appendChild(cityElement);

            for (int k = 0; k < rootItem->child(i)->child(j)->childCount(); k++)
            {
                if (rootItem->child(i)->child(j)->child(k)->childCount() > 0)
                {
                    QMessageBox::warning(this, QStringLiteral("警告"),
                                         QStringLiteral("抱歉，嵌套层太多，当前最多支持四层！"),
                                         QStringLiteral("确定"));
                    return false;
                }
                districtElement = doc.createElement(QStringLiteral("区"));
                districtText = doc.createTextNode(rootItem->child(i)->child(j)->child(k)->text(0));
                districtElement.appendChild(districtText);
                districtElement.setAttribute( "name", "District");
                //districtElement.setAttribute( "name", rootItem->child(i)->child(j)->child(k)->text(0));
                cityElement.appendChild(districtElement);
            }
        }
    }
    return true;
}

void XmlGenerator::on_btn_GenerateXML_clicked()
{
    if (!GenerateXML())
    {
        return;
    }
    QString path = QFileDialog::getSaveFileName(this, QStringLiteral("保存XML文件"),
                                                QCoreApplication::applicationDirPath(),
                                                tr("XML files (*.xml)"));
    if (path.isEmpty())
    {
        return;
    }
    if (path.endsWith(".xml"))
    {
        path = path.left(path.length() - 4);
    }
    path += ".xml";

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream out(&file);
    doc.save(out, 4);

    file.close();
}
