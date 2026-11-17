QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gate_factory.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    create_gate_presenter.hpp \
    gate_factory.hpp \
    mainwindow.h \
    model_to_views.hpp

INCLUDEPATH += $$PWD/../Gui/
INCLUDEPATH += $$PWD/../models/

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Gui/build/Desktop-Debug/release/ -lGui
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Gui/build/Desktop-Debug/debug/ -lGui
else:unix: LIBS += -L$$PWD/../Gui/build/Desktop-Debug/ -lGui

INCLUDEPATH += $$PWD/../Gui/build/Desktop-Debug
DEPENDPATH += $$PWD/../Gui/build/Desktop-Debug

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../models/build/Desktop-Debug/release/ -lmodels
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../models/build/Desktop-Debug/debug/ -lmodels
else:unix: LIBS += -L$$PWD/../models/build/Desktop-Debug/ -lmodels

INCLUDEPATH += $$PWD/../models/build/Desktop-Debug
DEPENDPATH += $$PWD/../models/build/Desktop-Debug
