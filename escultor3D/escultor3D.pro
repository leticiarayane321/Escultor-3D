QT -= gui
QT += core

CONFIG += c++11 console
CONFIG -= app_bundle

# --- LISTA DE FONTES (.cpp) ---
SOURCES += \
    main.cpp \
    sculptor.cpp \
    putvoxel.cpp \
    cutvoxel.cpp \
    putbox.cpp \
    cutbox.cpp \
    putsphere.cpp \
    cutsphere.cpp \
    putellipsoid.cpp \
    cutellipsoid.cpp

# --- LISTA DE HEADERS (.h) ---
HEADERS += \
    sculptor.h \
    figurageometrica.h \
    putvoxel.h \
    cutvoxel.h \
    putbox.h \
    cutbox.h \
    putsphere.h \
    cutsphere.h \
    putellipsoid.h \
    cutellipsoid.h
