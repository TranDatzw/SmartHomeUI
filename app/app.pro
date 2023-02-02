QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bath_room.cpp \
    bed_room.cpp \
    change_password.cpp \
    kitchen.cpp \
    living_room.cpp \
    main.cpp \
    main_room.cpp \
    mainwindow.cpp

HEADERS += \
    bath_room.h \
    bed_room.h \
    change_password.h \
    kitchen.h \
    living_room.h \
    main_room.h \
    mainwindow.h

FORMS += \
    bath_room.ui \
    bed_room.ui \
    change_password.ui \
    kitchen.ui \
    living_room.ui \
    main_room.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
