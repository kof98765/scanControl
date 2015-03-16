#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QDialog>
#include <QFileDialog>


namespace Ui {
class fileDialog;
}

class fileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit fileDialog(QWidget *parent = 0);
    ~fileDialog();


private:
    Ui::fileDialog *ui;
    QList<QString> list;
private slots:
    void openImgFiles();
    void textChange(QString str);
    void ok();
signals:
    void setFileList(QList<QString> list);


};

#endif // FILEDIALOG_H
