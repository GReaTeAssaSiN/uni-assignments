#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TablesManager.h"
#include "codeoperationtable.h"
#include "AdditionalListOfSymbolicNames.h"
#include "symbolicnamestable.h"
#include "passprocessor.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    TablesManager* TManager{};
    std::vector<AssemblerInstruction> sourceText_code{};
    CodeOperationTable opCode_table{};
    std::vector<OneSymbolicName> list_of_symb_names{};
    SymbolicNamesTable symb_table{};
    PassProcessor pp{};
    size_t step{};

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboBox_activated(int index);

    void on_tableWidget_ToOC_cellChanged(int row, int column);
    void on_tableWidget_ToSN_cellChanged(int row, int column);
    void on_textEdit_source_textChanged();

    void on_pushButton_pass_clicked();
    void on_pushButton_step_clicked();
    void on_pushButton_reset_clicked();

private:
    void setupGeometry();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
