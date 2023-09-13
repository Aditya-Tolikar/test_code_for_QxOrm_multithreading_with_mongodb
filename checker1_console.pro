QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

QX_BSON_INCLUDE_PATH=../mongoc/include/libbson-1.0/
QX_BSON_LIB_PATH=../mongoc/lib/
QX_MONGOC_INCLUDE_PATH=../mongoc/include/libmongoc-1.0/
QX_MONGOC_LIB_PATH=../mongoc/lib/

include($$PWD/../../../QxOrm/QxOrm/QxOrm.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        db_interactor.cpp \
        main.cpp \
        mainthingy.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../QxOrm/QxOrm/lib/ -lQxOrm
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../QxOrm/QxOrm/lib/ -lQxOrmd
else:unix: LIBS += -L$$PWD/../../../QxOrm/QxOrm/lib/ -lQxOrm

INCLUDEPATH += $$PWD/../../../QxOrm/QxOrm/include
DEPENDPATH += $$PWD/../../../QxOrm/QxOrm/include

HEADERS += \
    db_interactor.h \
    mainthingy.h

RESOURCES += \
    configs.qrc
