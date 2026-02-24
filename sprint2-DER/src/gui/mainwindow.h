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

#include "../src/lib/infra/factory/Factory.h"
#include "../lib/domain/Despesa.h"
#include "../lib/services/ServicoDespesas.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void registrarDespesa();
    void calcularDivisao();
    void apagarTodasDespesas();
    void gerarExtratoMensal();  // novo slot para extrato mensal

private:
    // ===== FORMULÁRIO =====
    QLineEdit *inputDescricao;
    QDoubleSpinBox *inputValor;
    QDateEdit *inputData;
    QPushButton *btnRegistrar;

    // ===== TABELA =====
    QTableWidget *tabelaDespesas;

    // ===== DIVISÃO =====
    QLabel *labelTotal;
    QSpinBox *inputMoradores;
    QLabel *labelValorPorMorador;

    // ===== BOTÕES =====
    QPushButton *btnApagarTodas;
    QPushButton *btnExtratoMensal; // botão extrato mensal

    // ===== TITULO =====
    QLabel *titulo;

    // ===== SERVIÇO =====
    ServicoDespesas servico;

    // ===== MÉTODOS AUXILIARES =====
    void atualizarTabela();
    double calcularTotalDespesas();
};

#endif