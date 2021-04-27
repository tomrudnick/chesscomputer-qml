QT += quick

CONFIG += c++17



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        chess.cpp \
        chessHelper.cpp \
        chesscom.cpp \
        chessmove.cpp \
        chesspieces/bishop.cpp \
        chesspieces/chesspiece.cpp \
        chesspieces/king.cpp \
        chesspieces/knight.cpp \
        chesspieces/pawn.cpp \
        chesspieces/queen.cpp \
        chesspieces/rook.cpp \
        main.cpp \
        uci/uci.cpp

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
    chess.h \
    chessHelper.h \
    chesscom.h \
    chessmove.h \
    chesspieces/bishop.h \
    chesspieces/chesspiece.h \
    chesspieces/king.h \
    chesspieces/knight.h \
    chesspieces/pawn.h \
    chesspieces/queen.h \
    chesspieces/rook.h \
    uci/uci.h
