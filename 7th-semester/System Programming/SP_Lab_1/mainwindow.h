#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Manager.h"
#include "TableCodeOperation.h"
#include "StructSupportTable.h"
#include "SymbolicNameTable.h"
#include "FirstPassProcessor.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Manager* manager{};
    std::vector<AssemblerInstruction> source_code{};
    TableCodeOperation opcode_table{};
    std::vector<SupportTable> sup_table{};;
    SymbolicNameTable symbolic_table{};
    FirstPassProcessor FPP{};

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /*Методы для реагирования на взаимодействие пользователя с интерфейсом*/
    void on_tableWidget_ToOC_cellChanged(int row, int column);\
    void on_tableWidget_auxTable_cellChanged(int row, int column);
    void on_tableWidget_ToSN_cellChanged(int row, int column);
    void on_comboBox_currentIndexChanged(int index);

    /*Основные кнопки*/
    void on_pushButton_first_clicked(); //Обработка первого прохода.
    void on_pushButton_second_clicked();//Обработка второго прохода.

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
