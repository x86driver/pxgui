LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    sdlw.cpp \
    TButton.cpp \
    TGui.cpp \
    TGuiElement.cpp \
    TWindow.cpp \
    TText.cpp \
    utils.cpp \
    TPage.cpp \
    TTimer.cpp

LOCAL_C_INCLUDES := /home/shane/pro/libsdl/SDL-1.2.14/include
LOCAL_C_INCLUDES += /home/shane/source/include/ /home/shane/source/include/freetype2
LOCAL_C_INCLUDES += external/sdl_ttf
LOCAL_C_INCLUDES += vendor/garmin/external/ustl
LOCAL_STATIC_LIBRARIES := libSDL libSDL_ttf libfreetype libustl
LOCAL_SHARED_LIBRARIES := libts
LOCAL_CFLAGS += -Wall -Wextra -Weffc++ -std=gnu++0x -DBUILD_FOR_ANDROID -DUSE_USTL -O2

LOCAL_MODULE:= gui

LOCAL_PRELINK_MODULE:=false

include $(BUILD_EXECUTABLE)

