QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database/aircraftTable.cpp \
    database/database.cpp \
    database/flightView.cpp \
    database/table.cpp \
    database/townTable.cpp \
    dialogs/editAircraftDialog.cpp \
    dialogs/editscheduledialog.cpp \
    dialogs/edittowndialog.cpp \
    dialogs/logindialog.cpp \
    logger.cpp \
    main.cpp \
    mainwindow.cpp \
    pages/aircraftPage.cpp \
    pages/flightsPage.cpp \
    pages/homepage.cpp \
    pages/page.cpp \
    pages/ticketspage.cpp \
    pages/townspage.cpp \
    utils.cpp

HEADERS += \
    database/aircraftTable.h \
    database/database.h \
    database/flightView.h \
    database/models/aircraftModel.h \
    database/models/flightModel.h \
    database/models/townModel.h \
    database/responses/aircraftTableResponses.h \
    database/responses/flightViewResponses.h \
    database/responses/response.h \
    database/responses/townTableResponses.h \
    database/table.h \
    database/townTable.h \
    dialogs/editAircraftDialog.h \
    dialogs/editscheduledialog.h \
    dialogs/edittowndialog.h \
    dialogs/logindialog.h \
    logger.h \
    mainwindow.h \
    models/model.h \
    models/townModel.h \
    pages/aircraftPage.h \
    pages/flightsPage.h \
    pages/homepage.h \
    pages/page.h \
    pages/ticketspage.h \
    pages/townspage.h \
    utils.h

FORMS += \
    dialogs/editAircraftDialog.ui \
    dialogs/editscheduledialog.ui \
    dialogs/edittowndialog.ui \
    dialogs/logindialog.ui \
    mainwindow.ui \
    pages/aircraftPage.ui \
    pages/flightsPage.ui \
    pages/homepage.ui \
    pages/ticketspage.ui \
    pages/townspage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
