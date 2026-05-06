QT += widgets
QT += multimedia

CONFIG += c++17

SRC_DIR = src
APP_DIR = $$SRC_DIR/app

SOURCES += \
    src/app/createprojectdialog.cpp \
    src/app/editormain.cpp \
    src/main.cpp \
    src/app/startupwindow.cpp \
    src/serialization/project.cpp \
    src/serialization/projectio.cpp \
    src/serialization/track.cpp \
    src/widgets/adjustableprogressbar.cpp \
    src/widgets/filedropwidget.cpp \
    src/widgets/nouserselectlistwidget.cpp \
    src/widgets/reorderabletablewidget.cpp

HEADERS += \
    src/app/createprojectdialog.h \
    src/app/editormain.h \
    src/app/startupwindow.h \
    src/serialization/project.h \
    src/serialization/projectio.h \
    src/serialization/track.h \
    src/widgets/adjustableprogressbar.h \
    src/widgets/filedropwidget.h \
    src/widgets/nouserselectlistwidget.h \
    src/widgets/reorderabletablewidget.h

FORMS += \
    src/app/createprojectdialog.ui \
    src/app/editormain.ui \
    src/app/startupwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
