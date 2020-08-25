QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

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
    linenumberarea.cpp \
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
    globals.h \
    linenumberarea.h \
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

RESOURCES += \
    images.qrc \
    shaders.qrc \
    style.qrc

DISTFILES += \
    stylesheet.qss

win32-msvc* {

INCLUDEPATH += $$PWD/../external/SpvShaderCompiler/include

LIBS += -L$$PWD/../external/SpvShaderCompiler/lib -lSpvShaderCompiler
LIBS += -L$$PWD/../external/SpvShaderCompiler/lib -lGenericCodeGen
LIBS += -L$$PWD/../external/SpvShaderCompiler/lib -lglslang
LIBS += -L$$PWD/../external/SpvShaderCompiler/lib -lHLSL
LIBS += -L$$PWD/../external/SpvShaderCompiler/lib -lMachineIndependent
LIBS += -L$$PWD/../external/SpvShaderCompiler/lib -lOGLCompiler
LIBS += -L$$PWD/../external/SpvShaderCompiler/lib -lOSDependent
LIBS += -L$$PWD/../external/SpvShaderCompiler/lib -lSPIRV
LIBS += -L$$PWD/../external/SpvShaderCompiler/lib -lSPVRemapper

}

linux-g++ {

INCLUDEPATH += $$PWD/../external/linux/SpvShaderCompiler/include

LIBS += -L$$PWD/../external/linux/SpvShaderCompiler/lib -lSpvShaderCompiler
LIBS += -L$$PWD/../external/linux/SpvShaderCompiler/lib -lglslang
LIBS += -L$$PWD/../external/linux/SpvShaderCompiler/lib -lHLSL
LIBS += -L$$PWD/../external/linux/SpvShaderCompiler/lib -lMachineIndependent
LIBS += -L$$PWD/../external/linux/SpvShaderCompiler/lib -lOGLCompiler
LIBS += -L$$PWD/../external/linux/SpvShaderCompiler/lib -lOSDependent
LIBS += -L$$PWD/../external/linux/SpvShaderCompiler/lib -lSPIRV
LIBS += -L$$PWD/../external/linux/SpvShaderCompiler/lib -lSPVRemapper
LIBS += -L$$PWD/../external/linux/SpvShaderCompiler/lib -lGenericCodeGen

}
