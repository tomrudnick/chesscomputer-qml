QT += quick

CONFIG += c++17



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        bishop.cpp \
        chess.cpp \
        chessHelper.cpp \
        chesscom.cpp \
        chessmove.cpp \
        chesspiece.cpp \
        king.cpp \
        knight.cpp \
        main.cpp \
        pawn.cpp \
        queen.cpp \
        rook.cpp \
        uci.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    bishop.h \
    chess.h \
    chessHelper.h \
    chesscom.h \
    chessmove.h \
    chesspiece.h \
    king.h \
    knight.h \
    pawn.h \
    queen.h \
    rook.h \
    uci.h
