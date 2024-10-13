#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tablesmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    TablesManager* manager{};
    std::vector<SourceAssemblyCode> source_code{};
    std::vector<OpcodeTable> opcode_table{};

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /*Методы для реагирования на взаимодействие пользователя с интерфейсом*/
    void on_tableWidget_ToOC_cellChanged(int row, int column);
    /*Основные кнопки*/
    void on_pushButton_first_clicked(); //Обработка первого прохода.
    void on_pushButton_second_clicked();//Обработка второго прохода.

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
