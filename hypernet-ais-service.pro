#-------------------------------------------------
#
# Project created by QtCreator 2022-03-31T15:41:56
#
#-------------------------------------------------

QT       += core network serialport websockets
QT       -= gui

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

CONFIG += c++11

#MODE += DEBUG_MODE

equals(MODE,"DEBUG_MODE") {
    TARGET = ais-service-console
    CONFIG += console
}
else {
    TARGET = ais-service
}

SOURCES += \
    di/di.cpp \
    domain/ais/ais_target_model.cpp \
    infra/database/ais/memory/trackrepository_mem.cpp \
    infra/stream/device_wrapper.cpp \
    infra/stream/serial_device_wrapper.cpp \
    interface/ais_input.cpp \
    interface/ais_output/ais_output_websocket_server.cpp \
    interface/data_input_adjuster.cpp \
    shared/configuration.cpp \
    shared/error/base_error.cpp \
    shared/error/err_file.cpp \
    usecase/ais_parser/ais_input_service.cpp \
    main.cpp \
    infra/stream/stream.cpp \
    usecase/ais_sender/ais_output_serializer_json.cpp \
    usecase/ais_sender/ais_output_service.cpp

HEADERS += \
    di/di.h \
    domain/ais/ais_target_model.h \
    domain/ais/ais_target_repository.h \
    infra/database/ais/memory/trackrepository_mem.h \
    infra/stream/device_wrapper.h \
    infra/stream/serial_device_wrapper.h \
    interface/ais_input.h \
    interface/ais_output/ais_output.h \
    interface/ais_output/ais_output_websocket_server.h \
    interface/data_input_adjuster.h \
    shared/configuration.h \
    shared/error/base_error.h \
    shared/error/err_file.h \
    usecase/ais_parser/ais_input_service.h \
    infra/stream/stream.h \
    usecase/ais_sender/ais_output_serializer.h \
    usecase/ais_sender/ais_output_serializer_json.h \
    usecase/ais_sender/ais_output_service.h

unix: {
    LIBS += -L/usr/lib/AISLib -lAISLib

    INCLUDEPATH += /usr/include/AISLib
    DEPENDPATH += /usr/include/AISLib

} else:win32 {
    INCLUDEPATH +=C:\Users\ms_tensai\AISLib\include\2024\v1
    DEPENDPATH += C:\Users\ms_tensai\AISLib\lib\2024\v1
}

win32:CONFIG(release, debug|release): LIBS += -LC:\Users\ms_tensai\AISLib\lib\2024\v1 -lAISLib
else:win32:CONFIG(debug, debug|release): LIBS += -LC:\Users\ms_tensai\AISLib\lib\2024\v1 -lAISLib
