QT += widgets

CONFIG += c++17

SRC_DIR = src
APP_DIR = $$SRC_DIR/app

SOURCES += \
    src/app/editormain.cpp \
    src/main.cpp \
    src/app/startupwindow.cpp

HEADERS += \
    src/app/editormain.h \
    src/app/startupwindow.h

FORMS += \
    src/app/editormain.ui \
    src/app/startupwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
