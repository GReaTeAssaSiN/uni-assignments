#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "PassProcessor.h"

//Конструктор.
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , manager(new Manager())
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(100, 40, 1176, 751);
    //Настройка ComboBox.
    ui->comboBox->addItem("Пример. По умолчанию (без ошибок)");
    ui->comboBox->addItem("Пользовательский ввод (чисто)");
    ui->comboBox->setCurrentIndex(0);
    //Вторая кнопка неактивна.
    ui->pushButton_second->setEnabled(false);
}

//Деструктор.
MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
    source_code.clear();
    opcode_table.Clear();
    symbolic_table.Clear();
    sup_table.clear();
}

//Обработка при изменении значений ячеек ТКО.
void MainWindow::on_tableWidget_ToOC_cellChanged(int row, int column)
{
    manager->UpdateRowInSpecifiedTable(ui->tableWidget_ToOC, row, column);
    manager->TableCodeOperationFormatBinaryOpcode(ui->tableWidget_ToOC);

    //Очистка вспомогательной таблицы, ТСИ, заголовка объектного модуля и двоичного кода.
    ui->tableWidget_auxTable->clear();
    ui->tableWidget_auxTable->setColumnCount(0);
    ui->tableWidget_auxTable->setRowCount(0);

    ui->tableWidget_ToSN->clear();
    ui->tableWidget_ToSN->setColumnCount(0);
    ui->tableWidget_ToSN->setRowCount(0);

    ui->tableWidget_OMH->clear();
    ui->tableWidget_OMH->setColumnCount(0);
    ui->tableWidget_OMH->setRowCount(0);

    ui->textEdit_binary_code->clear();

    //Очистка ошибок.
    ui->textEdit_FPE->clear();
    ui->textEdit_SPE->clear();

    //Включение кнопок.
    if (!ui->pushButton_first->isEnabled()){
        ui->pushButton_first->setEnabled(true);
        ui->pushButton_second->setEnabled(false);
    }
}

//Обработка при изменении ячеек вспомогательной таблицы (программно).
void MainWindow::on_tableWidget_auxTable_cellChanged(int row, int column)
{
    manager->UpdateRowInSpecifiedTable(ui->tableWidget_auxTable, row, column);
}

//Обработка при изменении ячеек ТСИ (программно).
void MainWindow::on_tableWidget_ToSN_cellChanged(int row, int column)
{
    manager->UpdateRowInSpecifiedTable(ui->tableWidget_ToSN, row, column);
}

//Изменение исходного кода ассемблирующей программы.
void MainWindow::on_textEdit_source_textChanged()
{
    //Очистка вспомогательной таблицы, ТСИ, заголовка объектного модуля и двоичного кода.
    ui->tableWidget_auxTable->clear();
    ui->tableWidget_auxTable->setColumnCount(0);
    ui->tableWidget_auxTable->setRowCount(0);

    ui->tableWidget_ToSN->clear();
    ui->tableWidget_ToSN->setColumnCount(0);
    ui->tableWidget_ToSN->setRowCount(0);

    ui->tableWidget_OMH->clear();
    ui->tableWidget_OMH->setColumnCount(0);
    ui->tableWidget_OMH->setRowCount(0);

    ui->textEdit_binary_code->clear();

    //Очистка ошибок.
    ui->textEdit_FPE->clear();
    ui->textEdit_SPE->clear();

    //Включение кнопок.
    if (!ui->pushButton_first->isEnabled()){
        ui->pushButton_first->setEnabled(true);
        ui->pushButton_second->setEnabled(false);
    }
}


//Если изменяется выбор в ComboBox - загружаются исходный текст ассемблирующей программы и ТКО по умолчанию (пример).
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    //Очистка вспомогательной таблицы, ТСИ, заголовка объектного модуля и двоичного кода.
    ui->tableWidget_auxTable->clear();
    ui->tableWidget_auxTable->setColumnCount(0);
    ui->tableWidget_auxTable->setRowCount(0);

    ui->tableWidget_ToSN->clear();
    ui->tableWidget_ToSN->setColumnCount(0);
    ui->tableWidget_ToSN->setRowCount(0);

    ui->tableWidget_OMH->clear();
    ui->tableWidget_OMH->setColumnCount(0);
    ui->tableWidget_OMH->setRowCount(0);

    ui->textEdit_binary_code->clear();

    //Очистка ошибок.
    ui->textEdit_FPE->clear();
    ui->textEdit_SPE->clear();

    //Включение кнопок.
    if (!ui->pushButton_first->isEnabled()){
        ui->pushButton_first->setEnabled(true);
        ui->pushButton_second->setEnabled(false);
    }

    switch(index){
    case 0:
        manager->ExportDataToTextEditSource(ui->textEdit_source);
        manager->ExportDataToTableWidgetToOC(ui->tableWidget_ToOC);
        break;
    case 1:
        manager->ExportCustomDataToTextEditSource(ui->textEdit_source);
        manager->ExportCustomDataToTableWidgetToOC(ui->tableWidget_ToOC);
        break;
    default:
        break;
    }
}

//Обработка нажатия на кнопку "Первый проход".
void MainWindow::on_pushButton_first_clicked()
{
    //Очистка структур.
    this->source_code.clear();
    this->opcode_table.Clear();
    this->sup_table.clear();
    this->symbolic_table.Clear();
    //Заполнение исходных структур данными.
    this->source_code = manager->ImportSourceAssemblerCodeFromField(ui->textEdit_source);
    this->opcode_table = manager->ImportTCOFromTableCodeOperation(ui->tableWidget_ToOC);
    //Очистка элементов интерфейса второго прохода.
    ui->tableWidget_OMH->clear();
    ui->tableWidget_OMH->setColumnCount(0);
    ui->tableWidget_OMH->setRowCount(0);
    ui->textEdit_binary_code->clear();
    ui->textEdit_SPE->clear();

    if(!this->PP.FirstPass(source_code, opcode_table, ui->tableWidget_auxTable, sup_table, ui->tableWidget_ToSN,
                                         symbolic_table, ui->textEdit_FPE)){
        //Очищаем элементы интерфейса.
        ui->tableWidget_auxTable->clear();
        ui->tableWidget_auxTable->setColumnCount(0);
        ui->tableWidget_auxTable->setRowCount(0);

        ui->tableWidget_ToSN->clear();
        ui->tableWidget_ToSN->setColumnCount(0);
        ui->tableWidget_ToSN->setRowCount(0);

        ui->tableWidget_OMH->clear();
        ui->tableWidget_OMH->setColumnCount(0);
        ui->tableWidget_OMH->setRowCount(0);

        ui->textEdit_binary_code->clear();

        //Ошибки должно быть видно.
    }
    else{
        ui->tableWidget_auxTable->resizeColumnsToContents();
        //Визуализация кнопок.
        ui->pushButton_second->setEnabled(true);
        ui->pushButton_first->setEnabled(false);
    }
}

//Обработка нажатия на кнопку "Второй проход".
void MainWindow::on_pushButton_second_clicked()
{
    if(!this->PP.SecondPass(ui->tableWidget_OMH, ui->textEdit_SPE, ui->textEdit_binary_code, sup_table, symbolic_table)){
        //Очищаем элементы интерфейса.
        ui->tableWidget_OMH->clear();
        ui->tableWidget_OMH->setColumnCount(0);
        ui->tableWidget_OMH->setRowCount(0);

        ui->textEdit_binary_code->clear();

        //Ошибки должно быть видно.
    }
    else{
        ui->tableWidget_OMH->resizeColumnsToContents();
    }
    //Визуализация кнопок.
    ui->pushButton_first->setEnabled(true);
    ui->pushButton_second->setEnabled(false);
}
