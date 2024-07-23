QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += structures widgets

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    structures/book.cpp \
    structures/bookitem.cpp \
    structures/rack.cpp \
    structures/shelf.cpp \
    structures/stack.cpp \
    structures/table.cpp \
    widgets/actionswidget.cpp \
    widgets/parameterswidget.cpp \
    widgets/viewwidget.cpp

HEADERS += \
    mainwindow.h \
    structures/book.h \
    structures/bookitem.h \
    structures/constants.h \
    structures/rack.h \
    structures/shelf.h \
    structures/stack.h \
    structures/table.h \
    widgets/actionswidget.h \
    widgets/parameterswidget.h \
    widgets/viewwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
