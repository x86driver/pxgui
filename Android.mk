LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    stl.cpp

LOCAL_C_INCLUDES += vendor/garmin/external/ustl
LOCAL_STATIC_LIBRARIES := libustl
LOCAL_CFLAGS += -Wall -Wextra -Weffc++ -std=gnu++0x -DBUILD_FOR_ANDROID -g -DUSE_USTL

LOCAL_MODULE:= stl

LOCAL_PRELINK_MODULE:=false

include $(BUILD_EXECUTABLE)

