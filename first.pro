#-------------------------------------------------
#
# Project created by QtCreator 2014-09-26T11:46:23
#
#-------------------------------------------------

QT       += core gui network axcontainer widgets opengl

#greaterThan(QT_MAJOR_VERSION, 4): QT +=

TARGET = first
TEMPLATE = app
RC_ICONS = ico/ico.ico

#includes
INCLUDEPATH += "$$(HALCONROOT)/include"
INCLUDEPATH += "$$(HALCONROOT)/include/cpp"
INCLUDEPATH += "$$(PCL_ROOT)/3rdParty/Boost/include"
INCLUDEPATH += "$$(PCL_ROOT)/3rdParty/Eigen/include"
INCLUDEPATH += "$$(PCL_ROOT)/3rdParty/FLANN/include"
INCLUDEPATH += "$$(PCL_ROOT)/include/pcl-1.6"
INCLUDEPATH += "$$(PCL_ROOT)/3rdParty/Qhull/include"
INCLUDEPATH+="lua/include"

#INCLUDEPATH+= "D:/opencv/include/opencv"
DEFINES+=QWT_DLL PCLLIBRARYDLL _AFXDLL
DEFINES-= MD UNICODE

UI_DIR+=release
#libs
QMAKE_LIBDIR  += "$$(HALCONROOT)/lib/x86sse2-win32"
QMAKE_LIBDIR  +="$$(PCL_ROOT)"/lib
QMAKE_LIBDIR +="../pcl"
QMAKE_LIBDIR+="../lua"

#QMAKE_LIBDIR +=./
LIBS    +=halcon.lib halconcpp.lib lua53.lib qwt.lib  pcl_io_release.lib  pcl_common_release.lib PCL_Library_Dll.lib



SOURCES += main.cpp\
        mainwindow.cpp \
    robot.cpp \
    reflectcontrol.cpp \
    summarizing.cpp \
    halconclass.cpp \
    tvplot.cpp \
    record.cpp \
    pointanalyze.cpp \
    plot.cpp \
    getProfiles/DllLoader.cpp \
    getProfiles/InterfaceLLT_2.cpp \
    profileget.cpp \
    msghandlerwapper.cpp \
    settingDialog.cpp \
    glwidget.cpp \
    imgListView.cpp\
    profileget.cpp \
    lua/lua.cpp




HEADERS  += mainwindow.h \
    robot.h \
    reflectcontrol.h \
    summarizing.h \
    halconclass.h \
    tvplot.h \
    record.h \
    pointanalyze.h \
    plot.h \
    settings.h \
    getProfiles/DllLoader.h \
    getProfiles/InterfaceLLT_2.h \
    getProfiles/resource.h \
    getProfiles/scanControlDataTypes.h \
    getProfiles/stdafx.h \
    profileget.h \
    msghandlerwapper.h \
    settingDialog.h \
    glwidget.h \
    pcl/PCL_Library_Dll.h \
    imgListView.h \
    profileget.h \
    lua/lua.h


FORMS    += mainwindow.ui \
    data_analyze.ui \
    pointanalyze.ui \
    settingDialog.ui

RESOURCES += \
    icons.qrc \
    ico/ico.qrc





