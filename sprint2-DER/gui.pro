QT += widgets sql
CONFIG += c++17

TEMPLATE = app
TARGET = sgpr_gui

SOURCES += \
    src/gui/main.cpp \
    src/gui/mainwindow.cpp \
    src/lib/domain/*.cpp \
    src/lib/services/*.cpp \
    src/lib/infra/factory/*.cpp \
    src/lib/infra/repository/*.cpp \
    src/lib/infra/persistence/*.cpp

HEADERS += \
    src/gui/mainwindow.h

FORMS += \
    mainwindow.ui \
    src/gui/mainwindow.ui

INCLUDEPATH += src/lib

# Diretório onde ficarão os arquivos objeto (.o)
OBJECTS_DIR = $$PWD/bin

# Diretório para arquivos gerados pelo moc
MOC_DIR = $$PWD/bin

# Diretório para arquivos ui (se usar .ui)
UI_DIR = $$PWD/bin

# Diretório para arquivos rcc (se usar resources)
RCC_DIR = $$PWD/bin