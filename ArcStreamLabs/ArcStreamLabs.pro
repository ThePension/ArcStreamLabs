QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += C:\opencv\build\include

LIBS += C:\opencv-build\bin\libopencv_core455.dll
LIBS += C:\opencv-build\bin\libopencv_highgui455.dll
LIBS += C:\opencv-build\bin\libopencv_imgcodecs455.dll
LIBS += C:\opencv-build\bin\libopencv_imgproc455.dll
LIBS += C:\opencv-build\bin\libopencv_features2d455.dll
LIBS += C:\opencv-build\bin\libopencv_calib3d455.dll
LIBS += C:\opencv-build\bin\libopencv_videoio455.dll

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
