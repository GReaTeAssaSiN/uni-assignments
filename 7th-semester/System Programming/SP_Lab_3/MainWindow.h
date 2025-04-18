#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Manager.h"
#include "TableCodeOperation.h"
#include "SupportTable.h"
#include "SymbolicNameTable.h"
#include "PassProcessor.h"

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
    PassProcessor PP{};
    int type_addr{};

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /*Методы для реагирования на взаимодействие пользователя с интерфейсом*/
    void on_tableWidget_ToOC_cellChanged(int row, int column);
    void on_tableWidget_auxTable_cellChanged(int row, int column);
    void on_tableWidget_ToSN_cellChanged(int row, int column);
    void on_tableWidget_modTable_cellChanged(int row, int column);
    void on_textEdit_source_textChanged();
    void on_comboBox_currentIndexChanged(int index);

    /*Основные кнопки*/
    void on_pushButton_first_clicked(); //Обработка первого прохода.
    void on_pushButton_second_clicked();//Обработка второго прохода.

    void on_tableWidget_OMH_cellChanged(int row, int column);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
