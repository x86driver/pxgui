LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    sdlw.cpp \
    TButton.cpp \
    TGui.cpp \
    TGuiElement.cpp \
    TWindow.cpp

LOCAL_C_INCLUDES := /home/shane/pro/libsdl/SDL-1.2.14/include
LOCAL_STATIC_LIBRARIES := libSDL
LOCAL_SHARED_LIBRARIES := libts

LOCAL_MODULE:= gui


include $(BUILD_EXECUTABLE)

