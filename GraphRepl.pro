QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    codeeditor.cpp \
    environment.cpp \
    evaluator.cpp \
    lambda.cpp \
    linenumberarea.cpp \
    lisphighlighter.cpp \
    listobject.cpp \
    main.cpp \
    mainwindow.cpp \
    primitive.cpp \
    tokenstream.cpp \
    utils.cpp \
    value.cpp

HEADERS += \
    codeeditor.h \
    environment.h \
    evaluator.h \
    lambda.h \
    linenumberarea.h \
    lisphighlighter.h \
    listobject.h \
    mainwindow.h \
    primitive.h \
    tokenstream.h \
    utils.h \
    value.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    GraphRepl.pro.user \
    LICENSE \
    README.md \
    doc/basic_check.md \
    doc/basic_primitive.md \
    doc/math.md \
    doc/system.md \
    doc/type_check.md \
    img/screenshot_0.jpg \
    init.scm
