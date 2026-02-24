#include "mainwindow.h"

#include <QLabel>
#include <QHeaderView>
#include <QDate>
#include <QAbstractItemView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Sistema de Gerenciamento de Gastos");
    setMinimumSize(800, 500);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    // ===== TÍTULO =====
    titulo = new QLabel("💰 Controle de Despesas");
    titulo->setStyleSheet("font-size: 22px; font-weight: bold;");

    // ===== INPUTS =====
    inputDescricao = new QLineEdit();
    inputDescricao->setPlaceholderText("Descrição da despesa");

    inputValor = new QDoubleSpinBox();
    inputValor->setMaximum(1000000);
    inputValor->setPrefix("R$ ");
    inputValor->setDecimals(2);

    inputData = new QDateEdit();
    inputData->setCalendarPopup(true);
    inputData->setDate(QDate::currentDate());

    btnRegistrar = new QPushButton("Registrar Despesa");
    btnRegistrar->setCursor(Qt::PointingHandCursor);

    // ===== TABELA =====
    tabelaDespesas = new QTableWidget();
    tabelaDespesas->setColumnCount(3);
    tabelaDespesas->setHorizontalHeaderLabels(
        {"Descrição", "Valor", "Data"}
    );

    tabelaDespesas->horizontalHeader()->setStretchLastSection(true);
    tabelaDespesas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tabelaDespesas->setAlternatingRowColors(true);
    tabelaDespesas->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabelaDespesas->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // ===== LAYOUT FORMULÁRIO =====
    QHBoxLayout *formLayout = new QHBoxLayout();
    formLayout->setSpacing(10);
    formLayout->addWidget(inputDescricao);
    formLayout->addWidget(inputValor);
    formLayout->addWidget(inputData);
    formLayout->addWidget(btnRegistrar);

    // ===== LAYOUT PRINCIPAL =====
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->addWidget(titulo);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(tabelaDespesas);

    central->setLayout(mainLayout);

    // ===== ESTILO GLOBAL =====
    central->setStyleSheet(R"(
        QWidget {
            font-family: Segoe UI;
            font-size: 14px;
        }

        QLineEdit, QDoubleSpinBox, QDateEdit {
            padding: 6px;
            border: 1px solid #ccc;
            border-radius: 6px;
        }

        QLineEdit:focus, QDoubleSpinBox:focus, QDateEdit:focus {
            border: 1px solid #0078D7;
        }

        QPushButton {
            background-color: #0078D7;
            color: white;
            padding: 8px 15px;
            border-radius: 6px;
            font-weight: bold;
        }

        QPushButton:hover {
            background-color: #005a9e;
        }

        QTableWidget {
            border: 1px solid #ddd;
            border-radius: 8px;
            gridline-color: #eee;
        }

        QHeaderView::section {
            background-color: #0078D7;
            color: white;
            padding: 6px;
            border: none;
        }
    )");

    connect(btnRegistrar, &QPushButton::clicked,
            this, &MainWindow::registrarDespesa);

    atualizarTabela();
}

void MainWindow::registrarDespesa()
{
    auto servico = infra::factory::createServicoDespesas();

    servico.registrarDespesa(
        inputDescricao->text().toStdString(),
        inputValor->value(),
        inputData->date().toString("dd/MM/yyyy").toStdString()
    );

    atualizarTabela();

    // Limpa campos
    inputDescricao->clear();
    inputValor->setValue(0.0);
    inputData->setDate(QDate::currentDate());
}

void MainWindow::atualizarTabela()
{
    auto servico = infra::factory::createServicoDespesas();
    auto lista = servico.listarDespesas();

    tabelaDespesas->setRowCount(lista.size());

    for (int i = 0; i < static_cast<int>(lista.size()); ++i) {
        tabelaDespesas->setItem(i, 0,
            new QTableWidgetItem(
                QString::fromStdString(lista[i].getDescricao())));

        tabelaDespesas->setItem(i, 1,
            new QTableWidgetItem(
                QString("R$ %1").arg(lista[i].getValor(), 0, 'f', 2)));

        tabelaDespesas->setItem(i, 2,
            new QTableWidgetItem(
                QString::fromStdString(lista[i].getData())));
    }
}