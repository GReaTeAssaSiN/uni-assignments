#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "TablesManager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , TManager( new TablesManager())
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Установка положения окна.
    setupGeometry();
    //Установка выбора примеров.
    ui->comboBox->addItem("Пример по умолчанию (без ошибок)");
    ui->comboBox->activated(0);
    ui->pushButton_reset->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete TManager;
    sourceText_code.clear();
    opCode_table.clear();
    symb_table.clear();
}

void MainWindow::setupGeometry()
{
    this->setGeometry(250, 40, 1000, 800);
}

//Загрузка исходного текста программы и таблицы кодов операций (ТКО) из примеров.
void MainWindow::on_comboBox_activated(int index)
{
    //Очищаем элементы интерфейса.
    ui->textEdit_source->clear();

    ui->tableWidget_ToOC->clear();
    ui->tableWidget_ToOC->setColumnCount(0);
    ui->tableWidget_ToOC->setRowCount(0);

    ui->tableWidget_ToSN->clear();
    ui->tableWidget_ToSN->setColumnCount(0);
    ui->tableWidget_ToSN->setRowCount(0);

    ui->textEdit_Errors->clear();
    ui->textEdit_binary_code->clear();
    switch (index)
    {
    case 0:
        TManager->LoadDefaultAssemblerSourceCode(ui->textEdit_source);
        TManager->LoadDefaultAssemplerOperationCode(ui->tableWidget_ToOC);
        break;
    default:
        break;
    }
}

//Автоматическое обновление таблиц при вставке/удалении.
void MainWindow::on_tableWidget_ToOC_cellChanged(int row, int column)
{
    TManager->UpdateViewOfTable(ui->tableWidget_ToOC, row, column);
    //Если изменяется таблица ТКО, то очистить таблицу символических имен.
    ui->tableWidget_ToSN->clear();
    ui->tableWidget_ToSN->setColumnCount(0);
    ui->tableWidget_ToSN->setRowCount(0);

    ui->textEdit_Errors->clear();
    ui->textEdit_binary_code->clear();

    step = 0;
    //Разблокировать кнопки.
    ui->pushButton_pass->setEnabled(true);
    ui->pushButton_step->setEnabled(true);
    ui->pushButton_reset->setEnabled(false);
}
void MainWindow::on_tableWidget_ToSN_cellChanged(int row, int column)
{
    TManager->UpdateViewOfTable(ui->tableWidget_ToSN, row, column);
}
void MainWindow::on_textEdit_source_textChanged()
{
    //Если изменяется исходный текст программы, то очистить таблицу символических имен.
    ui->tableWidget_ToSN->clear();
    ui->tableWidget_ToSN->setColumnCount(0);
    ui->tableWidget_ToSN->setRowCount(0);

    ui->textEdit_Errors->clear();
    ui->textEdit_binary_code->clear();

    step = 0;
    //Разблокировать кнопки.
    ui->pushButton_pass->setEnabled(true);
    ui->pushButton_step->setEnabled(true);
    ui->pushButton_reset->setEnabled(false);
}

//Проход.
void MainWindow::on_pushButton_pass_clicked()
{
    if (step == 0)
    {
        //Очищаем все структуры.
        this->sourceText_code.clear();
        this->opCode_table.clear();
        this->list_of_symb_names.clear();
        this->symb_table.clear();
        //Очищаем элементы интерфейса.
        ui->tableWidget_ToSN->clear();
        ui->tableWidget_ToSN->setColumnCount(0);
        ui->tableWidget_ToSN->setRowCount(0);

        this->sourceText_code = TManager->ParseAssemblerSourceCode(ui->textEdit_source);
        TManager->ExportFormattedSourceAssemblerCodeToField(this->sourceText_code, ui->textEdit_source);
        if(!this->TManager->ParseAssemblerOperationCode(ui->tableWidget_ToOC, opCode_table, ui->textEdit_Errors))
            return;
    }
    if (!this->pp.Pass(ui->textEdit_Errors, sourceText_code, opCode_table, list_of_symb_names,
                       ui->tableWidget_ToSN, symb_table, true, step, ui->textEdit_binary_code))
    {
        ui->pushButton_pass->setEnabled(false);
        ui->pushButton_step->setEnabled(false);
        ui->pushButton_reset->setEnabled(true);
        return;
    }
    else
    {
        ui->tableWidget_ToSN->resizeColumnsToContents();
    }
    //Блокирование кнопок, кроме кнопки очистки.
    ui->pushButton_pass->setEnabled(false);
    ui->pushButton_step->setEnabled(false);
    ui->pushButton_reset->setEnabled(true);

}

void MainWindow::on_pushButton_step_clicked()
{
    if (step == 0)
    {
        //Очищаем все структуры.
        this->sourceText_code.clear();
        this->opCode_table.clear();
        this->list_of_symb_names.clear();
        this->symb_table.clear();
        //Очищаем элементы интерфейса.
        ui->tableWidget_ToSN->clear();
        ui->tableWidget_ToSN->setColumnCount(0);
        ui->tableWidget_ToSN->setRowCount(0);

        this->sourceText_code = TManager->ParseAssemblerSourceCode(ui->textEdit_source);
        TManager->ExportFormattedSourceAssemblerCodeToField(this->sourceText_code, ui->textEdit_source);
        if(!this->TManager->ParseAssemblerOperationCode(ui->tableWidget_ToOC, opCode_table, ui->textEdit_Errors))
            return;
    }
    if (!this->pp.OneStep(ui->textEdit_Errors, sourceText_code, opCode_table, list_of_symb_names,
                          ui->tableWidget_ToSN, symb_table, step, ui->textEdit_binary_code))
    {
        ui->pushButton_pass->setEnabled(false);
        ui->pushButton_step->setEnabled(false);
        ui->pushButton_reset->setEnabled(true);
        return;
    }
    else
    {
        ui->tableWidget_ToSN->resizeColumnsToContents();
    }
    this->step++;
    //Блокирование кнопок, кроме кнопки очистки.
    if (step == this->sourceText_code.size())
    {
        ui->pushButton_pass->setEnabled(false);
        ui->pushButton_step->setEnabled(false);
        ui->pushButton_reset->setEnabled(true);
    }
}

void MainWindow::on_pushButton_reset_clicked()
{
    //Очищаем элементы интерфейса.
    ui->tableWidget_ToSN->clear();
    ui->tableWidget_ToSN->setColumnCount(0);
    ui->tableWidget_ToSN->setRowCount(0);

    ui->textEdit_Errors->clear();
    ui->textEdit_binary_code->clear();

    //Очищаем все структуры.
    this->sourceText_code.clear();
    this->opCode_table.clear();
    this->list_of_symb_names.clear();
    this->symb_table.clear();


    //Разблокировать кнопки.
    ui->pushButton_pass->setEnabled(true);
    ui->pushButton_step->setEnabled(true);
    ui->pushButton_reset->setEnabled(false);

    this->step = 0;
}

