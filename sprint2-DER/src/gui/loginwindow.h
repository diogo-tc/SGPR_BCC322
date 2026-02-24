#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class LoginWindow : public QWidget {
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);

private slots:
    void realizarLogin();
    void registrarUsuario();

private:
    QLineEdit *campoUsuario;
    QLineEdit *campoSenha;
    QPushButton *botaoLogin;
    QPushButton *botaoRegistrar;
};

#endif