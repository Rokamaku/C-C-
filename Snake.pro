TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    snake.cpp \
    board.cpp \
    menu.cpp
LIBS += -lncurses

HEADERS += \
    snake.h \
    board.h \
    menu.h
