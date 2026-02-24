#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QSpinBox>

#include "../lib/services/ServicoDespesas.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void registrarDespesa();
    void calcularDivisao();
    void apagarTodasDespesas();

private:
    void atualizarTabela();
    double calcularTotalDespesas();

    // ===== Serviço =====
    ServicoDespesas servico;

    // ===== Componentes =====
    QLabel *titulo;

    QLineEdit *inputDescricao;
    QDoubleSpinBox *inputValor;
    QDateEdit *inputData;
    QPushButton *btnRegistrar;

    QTableWidget *tabelaDespesas;

    QLabel *labelTotal;
    QSpinBox *inputMoradores;
    QLabel *labelValorPorMorador;
    QPushButton *btnApagarTodas;
};

#endif