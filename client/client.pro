QT       += core gui websockets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialog.cpp \
    main.cpp \
    enterwindow.cpp

HEADERS += \
    dialog.h \
    enterwindow.h \
    systemmessage.h

FORMS += \
    dialog.ui \
    enterwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Устанавливаем путь для выходных бинарных файлов
CONFIG += release
DESTDIR = ../build-release

# Устанавливаем путь для объектных файлов, MOC, RCC и других временных файлов
OBJECTS_DIR = ../build-release/obj
MOC_DIR = ../build-release/moc
RCC_DIR = ../build-release/rcc
UI_DIR = ../build-release/ui

