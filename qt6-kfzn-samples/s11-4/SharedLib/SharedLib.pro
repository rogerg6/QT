QT += widgets

TEMPLATE = lib
DEFINES += SHAREDLIB_LIBRARY     # 定义了全局宏

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    tpendialog.cpp

HEADERS += \
    SharedLib_global.h \
    tpendialog.h

FORMS += \
    tpendialog.ui


# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

