#ifndef XMLGENERATOR_H
#define XMLGENERATOR_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QEvent>
#include <QDomDocument>

namespace Ui {
class XmlGenerator;
}

class XmlGenerator : public QMainWindow
{
    Q_OBJECT

public:
    explicit XmlGenerator(QWidget *parent = 0);
    ~XmlGenerator();

    void InitUi();
    bool GenerateXML();

protected:
     bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void CurrentItemChangedSlot(QTreeWidgetItem *current);

    void on_btn_addItem_clicked();

    void on_btn_addChildItem_clicked();

    void on_btn_delItem_clicked();

    void on_btn_GenerateXML_clicked();



    void on_btn_up_clicked();

    void on_btn_down_clicked();

    void on_btn_changeToFather_clicked();

    void on_btn_changeToChild_clicked();

private:
    Ui::XmlGenerator *ui;
    QTreeWidgetItem *rootItem;
    QDomDocument doc;
};

#endif // XMLGENERATOR_H
