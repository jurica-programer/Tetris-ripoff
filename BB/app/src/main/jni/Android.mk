LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_LDLIB +=-landroid

LOCAL_SRC_FILES := com_zoid_mega_bb_Fcn.c main.c
LOCAL_MODULE := com_zoid_mega_bb_Fcn

include $(BUILD_SHARED_LIBRARY)