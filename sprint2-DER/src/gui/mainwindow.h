#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Widgets
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>

// Layouts
#include <QVBoxLayout>
#include <QHBoxLayout>

// Infraestrutura
#include "../../src/lib/infra/factory/Factory.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    void registrarDespesa();

private:
    // ===== Componentes da Interface =====
    QLabel *titulo;

    QLineEdit *inputDescricao;
    QDoubleSpinBox *inputValor;
    QDateEdit *inputData;
    QPushButton *btnRegistrar;

    QTableWidget *tabelaDespesas;

    // ===== Métodos Internos =====
    void atualizarTabela();
};

#endif // MAINWINDOW_H