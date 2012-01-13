TEMPLATE = lib
TARGET = plotcomponentsplugin
CONFIG += qt plugin
QT += declarative quick

TARGET = $$qtLibraryTarget($$TARGET)
uri = delaitre.jeremie.plotcomponents

HEADERS += \
    plugin.hpp \
    valuemapper.hpp \
    logvaluemapper.hpp \
    scalemap.hpp \
    linearscale.hpp \
    curve.hpp \
    curvenode.hpp

SOURCES += \
    plugin.cpp \
    valuemapper.cpp \
    logvaluemapper.cpp \
    scalemap.cpp \
    linearscale.cpp \
    curve.cpp \
    curvenode.cpp

OTHER_FILES = qmldir \
    test.qml \
    ValueTick.qml \
    Scale.qml \
    Plot.qml

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target

    copy_qmlfiles.target = $$OUT_PWD/qmlfiles
    copy_qmlfiles.depends = $$_PRO_FILE_PWD_/*.qml
    copy_qmlfiles.commands = $(COPY) $$replace(copy_qmlfiles.depends, /, $$QMAKE_DIR_SEP) .
    QMAKE_EXTRA_TARGETS += copy_qmlfiles
    PRE_TARGETDEPS += $$copy_qmlfiles.target
}

qmldir.files = qmldir
qmlfiles.files = *.qml

symbian {
    TARGET.EPOCALLOWDLLDATA = 1
} else:unix {
    installPath = /usr/lib/qt4/imports/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    qmlfiles.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir qmlfiles
}
