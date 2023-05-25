QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database/database.cpp \
    database/models/aircraft.cpp \
    database/models/flight.cpp \
    database/models/ticket.cpp \
    database/models/town.cpp \
    dialogs/editAircraftDialog.cpp \
    dialogs/editFlightDialog.cpp \
    dialogs/editscheduledialog.cpp \
    dialogs/edittowndialog.cpp \
    dialogs/logindialog.cpp \
    logger.cpp \
    main.cpp \
    mainwindow.cpp \
    pages/aircraftPage.cpp \
    pages/flightsPage.cpp \
    pages/page.cpp \
    pages/schedulePage.cpp \
    pages/ticketspage.cpp \
    pages/townspage.cpp

HEADERS += \
    database/database.h \
    database/models/aircraft.h \
    database/models/flight.h \
    database/models/ticket.h \
    database/models/town.h \
    dialogs/editAircraftDialog.h \
    dialogs/editFlightDialog.h \
    dialogs/editscheduledialog.h \
    dialogs/edittowndialog.h \
    dialogs/logindialog.h \
    logger.h \
    mainwindow.h \
    models/model.h \
    models/townModel.h \
    pages/aircraftPage.h \
    pages/flightsPage.h \
    pages/page.h \
    pages/schedulePage.h \
    pages/ticketspage.h \
    pages/townspage.h

FORMS += \
    dialogs/editAircraftDialog.ui \
    dialogs/editFlightDialog.ui \
    dialogs/editscheduledialog.ui \
    dialogs/edittowndialog.ui \
    dialogs/logindialog.ui \
    mainwindow.ui \
    pages/aircraftPage.ui \
    pages/flightsPage.ui \
    pages/schedulePage.ui \
    pages/ticketspage.ui \
    pages/townspage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
