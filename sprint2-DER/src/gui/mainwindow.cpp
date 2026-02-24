#include "mainwindow.h"

#include <QHeaderView>
#include <QDate>
#include <QAbstractItemView>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Sistema de Gerenciamento de Gastos");
    setMinimumSize(900, 600);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    // ===== TITULO =====
    titulo = new QLabel("💰 Controle de Despesas");
    titulo->setStyleSheet("font-size: 22px; font-weight: bold;");

    // ===== FORMULÁRIO =====
    inputDescricao = new QLineEdit();
    inputDescricao->setPlaceholderText("Descrição");

    inputValor = new QDoubleSpinBox();
    inputValor->setMaximum(1000000);
    inputValor->setPrefix("R$ ");
    inputValor->setDecimals(2);

    inputData = new QDateEdit();
    inputData->setCalendarPopup(true);
    inputData->setDate(QDate::currentDate());

    btnRegistrar = new QPushButton("Registrar");

    QHBoxLayout *formLayout = new QHBoxLayout();
    formLayout->addWidget(inputDescricao);
    formLayout->addWidget(inputValor);
    formLayout->addWidget(inputData);
    formLayout->addWidget(btnRegistrar);

    // ===== TABELA =====
    tabelaDespesas = new QTableWidget();
    tabelaDespesas->setColumnCount(3);
    tabelaDespesas->setHorizontalHeaderLabels({"Descrição", "Valor", "Data"});
    tabelaDespesas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tabelaDespesas->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // ===== ÁREA DE DIVISÃO =====
    labelTotal = new QLabel("Total: R$ 0.00");
    labelTotal->setStyleSheet("font-weight: bold; font-size: 16px;");

    inputMoradores = new QSpinBox();
    inputMoradores->setMinimum(1);
    inputMoradores->setMaximum(50);
    inputMoradores->setValue(1);

    labelValorPorMorador = new QLabel("Cada morador paga: R$ 0.00");
    labelValorPorMorador->setStyleSheet("font-weight: bold;");

    btnApagarTodas = new QPushButton("Apagar Todas as Despesas");
    btnApagarTodas->setStyleSheet("background-color: #d9534f; color: white; padding: 6px;");

    btnExtratoMensal = new QPushButton("Gerar Extrato Mensal");
    btnExtratoMensal->setStyleSheet("background-color: #0275d8; color: white; padding: 6px;");

    QHBoxLayout *divisaoLayout = new QHBoxLayout();
    divisaoLayout->addWidget(labelTotal);
    divisaoLayout->addSpacing(20);
    divisaoLayout->addWidget(new QLabel("Total de moradores:"));
    divisaoLayout->addWidget(inputMoradores);
    divisaoLayout->addSpacing(20);
    divisaoLayout->addWidget(labelValorPorMorador);
    divisaoLayout->addStretch();
    divisaoLayout->addWidget(btnApagarTodas);

    // ===== LAYOUT PRINCIPAL =====
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);
    mainLayout->addWidget(titulo);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(tabelaDespesas);
    mainLayout->addLayout(divisaoLayout);
    mainLayout->addWidget(btnExtratoMensal); // botão extrato

    central->setLayout(mainLayout);

    // ===== CONEXÕES =====
    connect(btnRegistrar, &QPushButton::clicked, this, &MainWindow::registrarDespesa);
    connect(inputMoradores, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::calcularDivisao);
    connect(btnApagarTodas, &QPushButton::clicked, this, &MainWindow::apagarTodasDespesas);
    connect(btnExtratoMensal, &QPushButton::clicked, this, &MainWindow::gerarExtratoMensal);

    atualizarTabela();
}

// =============================

void MainWindow::registrarDespesa()
{
    if (!servico.registrarDespesa(
            inputDescricao->text().toStdString(),
            inputValor->value(),
            inputData->date().toString("dd/MM/yyyy").toStdString()))
    {
        QMessageBox::warning(this, "Erro",
                             "Preencha todos os campos corretamente.");
        return;
    }

    atualizarTabela();

    inputDescricao->clear();
    inputValor->setValue(0.0);
}

// =============================

double MainWindow::calcularTotalDespesas()
{
    auto lista = servico.listarDespesas();

    double total = 0.0;
    for (const auto &d : lista)
        total += d.getValor();

    return total;
}

// =============================

void MainWindow::calcularDivisao()
{
    double total = calcularTotalDespesas();
    int moradores = inputMoradores->value();

    double valorPorPessoa = (moradores > 0) ? total / moradores : 0.0;

    labelTotal->setText(QString("Total: R$ %1")
                        .arg(total, 0, 'f', 2));

    labelValorPorMorador->setText(
        QString("Cada morador paga: R$ %1")
        .arg(valorPorPessoa, 0, 'f', 2));
}

// =============================

void MainWindow::apagarTodasDespesas()
{
    if (QMessageBox::question(this, "Confirmar",
        "Tem certeza que deseja apagar todas as despesas?")
        == QMessageBox::Yes)
    {
        servico.apagarTodas();
        atualizarTabela();
        calcularDivisao();
    }
}

// =============================

void MainWindow::atualizarTabela()
{
    auto lista = servico.listarDespesas();

    tabelaDespesas->setRowCount(lista.size());

    for (int i = 0; i < static_cast<int>(lista.size()); ++i)
    {
        tabelaDespesas->setItem(i, 0,
            new QTableWidgetItem(QString::fromStdString(lista[i].getDescricao())));

        tabelaDespesas->setItem(i, 1,
            new QTableWidgetItem(QString("R$ %1")
                                 .arg(lista[i].getValor(), 0, 'f', 2)));

        tabelaDespesas->setItem(i, 2,
            new QTableWidgetItem(QString::fromStdString(lista[i].getData())));
    }

    calcularDivisao();
}

// =============================
// NOVO SLOT - EXTRATO MENSAL

void MainWindow::gerarExtratoMensal()
{
    auto lista = servico.listarDespesas();
    if (lista.empty()) {
        QMessageBox::information(this, "Extrato Mensal", "Nenhuma despesa registrada.");
        return;
    }

    // Identificar o último mês com registro
    int ultimoMes = 0;
    int ultimoAno = 0;
    for (const auto &d : lista) {
        QDate data = QDate::fromString(QString::fromStdString(d.getData()), "dd/MM/yyyy");
        if (!data.isValid()) continue;
        if (data.year() > ultimoAno || (data.year() == ultimoAno && data.month() > ultimoMes)) {
            ultimoAno = data.year();
            ultimoMes = data.month();
        }
    }

    // Filtrar despesas do último mês
    std::vector<Despesa> despesasMes;
    double totalMes = 0.0;
    for (const auto &d : lista) {
        QDate data = QDate::fromString(QString::fromStdString(d.getData()), "dd/MM/yyyy");
        if (data.isValid() && data.year() == ultimoAno && data.month() == ultimoMes) {
            despesasMes.push_back(d);
            totalMes += d.getValor();
        }
    }

    int moradores = inputMoradores->value();
    double valorPorMorador = (moradores > 0) ? totalMes / moradores : 0.0;

    // Criar diálogo
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Extrato Mensal");
    dialog->resize(600, 400);

    QVBoxLayout *layout = new QVBoxLayout(dialog);

    QLabel *labelMes = new QLabel(QString("Mês: %1/%2")
                                  .arg(ultimoMes, 2, 10, QChar('0'))
                                  .arg(ultimoAno));
    labelMes->setStyleSheet("font-weight: bold; font-size: 16px;");
    layout->addWidget(labelMes);

    QTableWidget *tabela = new QTableWidget();
    tabela->setColumnCount(3);
    tabela->setHorizontalHeaderLabels({"Descrição", "Valor", "Data"});
    tabela->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tabela->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tabela->setRowCount(despesasMes.size());
    for (int i = 0; i < static_cast<int>(despesasMes.size()); ++i) {
        tabela->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(despesasMes[i].getDescricao())));
        tabela->setItem(i, 1, new QTableWidgetItem(QString("R$ %1").arg(despesasMes[i].getValor(), 0, 'f', 2)));
        tabela->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(despesasMes[i].getData())));
    }

    layout->addWidget(tabela);

    QLabel *labelTotal = new QLabel(QString("Despesa total: R$ %1").arg(totalMes, 0, 'f', 2));
    labelTotal->setStyleSheet("font-weight: bold; font-size: 14px;");
    layout->addWidget(labelTotal);

    QLabel *labelPorMorador = new QLabel(QString("Valor a ser pago por cada morador: R$ %1").arg(valorPorMorador, 0, 'f', 2));
    labelPorMorador->setStyleSheet("font-weight: bold; font-size: 14px;");
    layout->addWidget(labelPorMorador);

    dialog->setLayout(layout);
    dialog->exec();
}