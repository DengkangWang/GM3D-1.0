QT       += core gui
QT 	 += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
INCLUDEPATH += eigen-3.4.0
LIBS += $$PWD\libfftw3-3.lib
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcubedialog.cpp \
    addcylinderdialog.cpp \
    addirregulardialog.cpp \
    addprismoiddialog.cpp \
    addspheredialog.cpp \
    bce.cpp \
    forwarding.cpp \
    forwarditem.cpp \
    main.cpp \
    mainwindow.cpp \
    modeling.cpp \
    mymodel.cpp \
    profile.cpp \
    qcustomplot.cpp \
    sourcesetting.cpp \
    using_checkbox_item.cpp

HEADERS += \
    addcubedialog.h \
    addcylinderdialog.h \
    addirregulardialog.h \
    addprismoiddialog.h \
    addspheredialog.h \
    bce.h \
    fftw3.h \
    forwarding.h \
    forwarditem.h \
    mainwindow.h \
    modeling.h \
    mymodel.h \
    profile.h \
    qcustomplot.h \
    sourcesetting.h \
    using_checkbox_item.h

FORMS += \
    addcubedialog.ui \
    addcylinderdialog.ui \
    addirregulardialog.ui \
    addprismoiddialog.ui \
    addspheredialog.ui \
    forwarding.ui \
    forwarditem.ui \
    mainwindow.ui \
    modeling.ui \
    profile.ui \
    sourcesetting.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    myicon.qrc

DISTFILES += \
    GM3D.pro.user \
    HomeIcon.ico \
    logo.rc
