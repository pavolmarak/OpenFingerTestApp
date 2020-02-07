#-------------------------------------------------
#
# Project created by QtCreator 2020-02-05T14:52:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenFingerTestApp
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CFLAGS_ISYSTEM=

DEFINES += PRO_PWD=\\\"$$_PRO_FILE_PWD_\\\"

CONFIG += c++17

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    zoomlabel.cpp

HEADERS += \
        mainwindow.h \
    zoomlabel.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


CONFIG += manjaro
#CONFIG += debian

debian {
    #CUDA - Debian
    INCLUDEPATH += /usr/local/cuda/include

    #Suprema SDK - Debian (installed manually)
    INCLUDEPATH += /usr/local/include/suprema

    #ArrayFire - Debian (built from source)
    unix:!macx: LIBS += -L/usr/local/lib/ -lafcuda
    INCLUDEPATH += /usr/local/include
    DEPENDPATH += /usr/local/include

    #OpenCV - Debian (as a package)
    unix:!macx: LIBS += -L/usr/lib/x86_64-linux-gnu/ -lopencv_core
    unix:!macx: LIBS += -L/usr/lib/x86_64-linux-gnu/ -lopencv_imgproc
    unix:!macx: LIBS += -L/usr/lib/x86_64-linux-gnu/ -lopencv_imgcodecs
    unix:!macx: LIBS += -L/usr/lib/x86_64-linux-gnu/ -lopencv_highgui
    INCLUDEPATH += /usr/include/opencv4
    DEPENDPATH += /usr/include/opencv4

    #glog, protobuf, boost - Debian (as a package)
    unix:!macx: LIBS += -L/usr/lib/x86_64-linux-gnu/ -lglog
    unix:!macx: LIBS += -L/usr/lib/x86_64-linux-gnu/ -lprotobuf
    unix:!macx: LIBS += -L/usr/lib/x86_64-linux-gnu/ -lboost_system
    INCLUDEPATH += /usr/include
    DEPENDPATH += /usr/include

    #QCustomPlot - Debian (built from source)
    unix:!macx: LIBS += -L/usr/local/lib/ -lqcustomplotd
    INCLUDEPATH += /usr/local/include
    DEPENDPATH += /usr/local/include
}

manjaro {
    #CUDA - Manjaro
    INCLUDEPATH += /opt/cuda/include

    #Suprema SDK - Manjaro (installed manually)
    INCLUDEPATH += /usr/local/include/suprema

    #ArrayFire - Manjaro (built from source)
    unix:!macx: LIBS += -L/usr/local/lib/ -lafcuda
    INCLUDEPATH += /usr/local/include
    DEPENDPATH += /usr/local/include

    #OpenCV - Manjaro (as a package)
    unix:!macx: LIBS += -L/usr/lib/ -lopencv_core
    unix:!macx: LIBS += -L/usr/lib/ -lopencv_imgproc
    unix:!macx: LIBS += -L/usr/lib/ -lopencv_imgcodecs
    unix:!macx: LIBS += -L/usr/lib/ -lopencv_highgui
    INCLUDEPATH += /usr/include/opencv4
    DEPENDPATH += /usr/include/opencv4

    #glog, protobuf, boost - Manjaro (as a package)
    unix:!macx: LIBS += -L/usr/lib/ -lglog
    unix:!macx: LIBS += -L/usr/lib/ -lprotobuf
    unix:!macx: LIBS += -L/usr/lib/ -lboost_system
    INCLUDEPATH += /usr/include
    DEPENDPATH += /usr/include

    #QCustomPlot - Manjaro (built from source)
    unix:!macx: LIBS += -L/usr/local/lib/ -lqcustomplotd
    INCLUDEPATH += /usr/local/include
    DEPENDPATH += /usr/local/include
}

#openfinger-preprocessor
unix:!macx: LIBS += -L$$PWD/../build-Preprocessing-Desktop-Debug/ -lPreprocessing
#unix:!macx: LIBS += -L$$PWD/../build-Preprocessing-Desktop-Release/ -lPreprocessing
INCLUDEPATH += $$PWD/../openfinger-preprocessor
DEPENDPATH += $$PWD/../openfinger-preprocessor

#openfinger-extractor
unix:!macx: LIBS += -L$$PWD/../build-Extraction-Desktop-Debug/ -lExtraction
#unix:!macx: LIBS += -L$$PWD/../build-Extraction-Desktop-Release/ -lExtraction
INCLUDEPATH += $$PWD/../openfinger-extractor
DEPENDPATH += $$PWD/../openfinger-extractor

#openfinger-matcher
unix:!macx: LIBS += -L$$PWD/../build-Matcher-Desktop-Debug/ -lMatcher
#unix:!macx: LIBS += -L$$PWD/../build-Matcher-Desktop-Release/ -lMatcher
INCLUDEPATH += $$PWD/../openfinger-matcher
DEPENDPATH += $$PWD/../openfinger-matcher
