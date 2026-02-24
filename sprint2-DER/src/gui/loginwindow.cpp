#include "loginwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent) {

    setWindowTitle("Login - SGPR");
    resize(300, 200);

    campoUsuario = new QLineEdit;
    campoUsuario->setPlaceholderText("Usuário");

    campoSenha = new QLineEdit;
    campoSenha->setPlaceholderText("Senha");
    campoSenha->setEchoMode(QLineEdit::Password);

    botaoLogin = new QPushButton("Entrar");
    botaoRegistrar = new QPushButton("Registrar");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(new QLabel("Login"));
    layout->addWidget(campoUsuario);
    layout->addWidget(campoSenha);
    layout->addWidget(botaoLogin);
    layout->addWidget(botaoRegistrar);

    setLayout(layout);

    connect(botaoLogin, &QPushButton::clicked, this, &LoginWindow::realizarLogin);
    connect(botaoRegistrar, &QPushButton::clicked, this, &LoginWindow::registrarUsuario);
}

void LoginWindow::realizarLogin() {
    QSqlQuery query;
    query.prepare("SELECT * FROM usuarios WHERE nome = :nome AND senha = :senha");
    query.bindValue(":nome", campoUsuario->text());
    query.bindValue(":senha", campoSenha->text());

    if(query.exec() && query.next()) {
        QMessageBox::information(this, "Sucesso", "Login realizado!");
        this->close();
    } else {
        QMessageBox::warning(this, "Erro", "Usuário ou senha inválidos.");
    }
}

void LoginWindow::registrarUsuario() {
    QSqlQuery query;
    query.prepare("INSERT INTO usuarios (nome, senha) VALUES (:nome, :senha)");
    query.bindValue(":nome", campoUsuario->text());
    query.bindValue(":senha", campoSenha->text());

    if(query.exec()) {
        QMessageBox::information(this, "Sucesso", "Usuário registrado!");
    } else {
        QMessageBox::warning(this, "Erro", "Erro ao registrar usuário.");
    }
}