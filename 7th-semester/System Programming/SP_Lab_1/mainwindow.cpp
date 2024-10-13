#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tablesmanager.h"
#include "GeneralFunctions.h"

//Конструктор.
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , manager(new TablesManager())
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Загрузка данных исходного текста и ТКО по умолчанию.
    manager->LoadDefaultAssemblerSourceCodeToField(ui->textEdit_source);
    manager->LoadDefaultOperationCodeToTable(ui->tableWidget_ToOC);
    ui->pushButton_second->setEnabled(false);
}

//Деструктор.
MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
    source_code.clear();
    opcode_table.clear();
}

//Обработка изменения значений ячеек ТКО.
void MainWindow::on_tableWidget_ToOC_cellChanged(int row, int column)
{
    manager->UpdateRowInSpecifiedTable(ui->tableWidget_ToOC, row, column);
    //Очистка данных перед новыми исходыми данными.
    ui->textEdit_FPE->clear();
    manager->ClearTable(ui->tableWidget_auxTable);
    manager->ClearTable(ui->tableWidget_ToSN);
    //Визуализация кнопок.
    ui->pushButton_first->setEnabled(true);
    ui->pushButton_second->setEnabled(false);
    //Форматирование столбца с двоичным кодом МКОП.
    manager->OpcodeTableFormatBinaryOpcode(ui->tableWidget_ToOC);
}

//Обработка нажатия на кнопку "Первый проход".
void MainWindow::on_pushButton_first_clicked()
{
    //Очистка старых данных.
    ui->textEdit_FPE->clear();
    manager->ClearTable(ui->tableWidget_auxTable);
    manager->ClearTable(ui->tableWidget_ToSN);
    //Загрузка новых данных.
    source_code = manager->GetAssemblerSourceCodeFromField(ui->textEdit_source);
    opcode_table = manager->GetOperationCodeTable(ui->tableWidget_ToOC);
    manager->LoadCustomAssemblerSourceCodeToField(ui->textEdit_source, source_code);
    manager->LoadCustomOperationCodeTable(ui->tableWidget_ToOC, opcode_table);
    if(FirstPass(source_code, opcode_table, ui->tableWidget_auxTable, ui->tableWidget_ToSN, ui->textEdit_FPE, manager)){
        //Визуализация кнопко.
        ui->pushButton_second->setEnabled(true);
        ui->pushButton_first->setEnabled(false);
    }
    ui->tableWidget_auxTable->resizeColumnsToContents();
}

//Обработка нажатия на кнопку "Второй проход".
void MainWindow::on_pushButton_second_clicked()
{
    //Вызов второго прохода, отключение кнопки 2, включение кнопки 1.
}

