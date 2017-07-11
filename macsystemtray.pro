#-------------------------------------------------
#
# Project created by QtCreator 2017-07-11T09:25:44
#
#-------------------------------------------------

QT       += core gui

# not put file on dir from Git or Subversion!!
MOC_DIR = .sand/.moc
RCC_DIR = .sand/.rcc
OBJECTS_DIR = .sand/.obj
# not put file on dir from Git or Subversion!!

# Mac specific setting
macx:CONFIG += lib_bundle
macx:QTPLUGIN     += qmng qjpeg qgif qtiff
# macx:RC_FILE = zzz.icns
macx:ICON = zzz.icns
macx:CONFIG += lib_bundle


CONFIG(release, debug|release) {
    # mytarget.target = ./zz_after_build.sh
    # mytarget.commands = touch $$mytarget.target

    # QMAKE_EXTRA_TARGETS +=mytarget
    # QMAKE_POST_LINK += mytarget
    QMAKE_POST_LINK += ./zz_after_build.sh
}


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MacSystemTray
macx:TEMPLATE = app


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h \
    trayglobal.h

RESOURCES += \
    currentapp.qrc

DISTFILES += Note  Info.plist \
             zz_after_build.sh


