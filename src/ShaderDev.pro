QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_CXXFLAGS_DEBUG += /MD

#------------------------------- Versioning

VERSION_MAJOR = 0
VERSION_MINOR = 1
VERSION_BUILD = 1

DEFINES += "VERSION_MAJOR=$$VERSION_MAJOR"\
           "VERSION_MINOR=$$VERSION_MINOR"\
           "VERSION_BUILD=$$VERSION_BUILD"

VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_BUILD}

#-------------------------------

SOURCES += \
    codeedit.cpp \
    controlswidget.cpp \
    main.cpp \
    mainwindow.cpp \
    outputedit.cpp \
    syntaxhighlighter.cpp \
    vulkanrenderer.cpp \
    vulkanview.cpp \
    vulkanwindow.cpp \
    windowmanager.cpp

HEADERS += \
    codeedit.h \
    controlswidget.h \
    mainwindow.h \
    outputedit.h \
    syntaxhighlighter.h \
    vulkanrenderer.h \
    vulkanview.h \
    vulkanwindow.h \
    windowmanager.h

FORMS += \
    controlswidget.ui \
    mainwindow.ui

CONFIG(debug, debug|release): DESTDIR = $$OUT_PWD
CONFIG(release, debug|release): DESTDIR = $$OUT_PWD

# Includes
INCLUDEPATH += $$PWD/../external/SpvShaderCompiler/include

# Libs
LIBS += -L$$PWD/../external/SpvShaderCompiler/lib -lSpvShaderCompiler
LIBS += -L$$PWD/../external/SpvShaderCompiler/lib -lGenericCodeGen
LIBS += -L$$PWD/../external/SpvShaderCompiler/lib -lglslang
LIBS += -L$$PWD/../external/SpvShaderCompiler/lib -lHLSL
LIBS += -L$$PWD/../external/SpvShaderCompiler/lib -lMachineIndependent
LIBS += -L$$PWD/../external/SpvShaderCompiler/lib -lOGLCompiler
LIBS += -L$$PWD/../external/SpvShaderCompiler/lib -lOSDependent
LIBS += -L$$PWD/../external/SpvShaderCompiler/lib -lSPIRV
LIBS += -L$$PWD/../external/SpvShaderCompiler/lib -lSPVRemapper

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
