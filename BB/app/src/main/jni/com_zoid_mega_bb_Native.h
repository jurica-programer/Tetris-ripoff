/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
#include <android/log.h>
#include "common_functions.h"
#include "global_functions.h"
#include "queue.h"
#include "blocks.h"
#include "FSM.h"
#include "buttons.h"

#ifndef _Included_com_zoid_mega_bb_Native
#define _Included_com_zoid_mega_bb_Native
#ifdef __cplusplus
extern "C" {
#endif

#define  LOG_TAG    "NATIVE_LOG"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)


/*
 * Class:     com_zoid_mega_bb_Native
 * Method:    startThread
 * Signature: ()Z
 */
JNIEXPORT jint JNICALL Java_com_zoid_mega_bb_Native_startThread(JNIEnv *, jclass);

/*
 * Class:     com_zoid_mega_bb_Native
 * Method:    startButton
 * Signature: ()Z
 */
JNIEXPORT jint JNICALL Java_com_zoid_mega_bb_Native_startButton(JNIEnv *, jclass, jint);
/*
 * Class:     com_zoid_mega_bb_Native
 * Method:    initGameRes
 * Signature: ()Z
 */
JNIEXPORT jint JNICALL Java_com_zoid_mega_bb_Native_initGameRes(JNIEnv *, jclass);

/*
 * Class:     com_zoid_mega_bb_Native
 * Method:    terminateGameRes
 * Signature: ()Z
 */
JNIEXPORT jint JNICALL Java_com_zoid_mega_bb_Native_terminateGameRes(JNIEnv *, jclass);

/*
 * Class:     com_zoid_mega_bb_Native
 * Method:    buttonA
 * Signature: ()Z
 */
JNIEXPORT jint JNICALL Java_com_zoid_mega_bb_Native_buttonA(JNIEnv *, jclass);

/*
 * Class:     com_zoid_mega_bb_Native
 * Method:    buttonAlong
 * Signature: ()Z
 */
JNIEXPORT jint JNICALL Java_com_zoid_mega_bb_Native_buttonAlong(JNIEnv *, jclass);

/*
 * Class:     com_zoid_mega_bb_Native
 * Method:    buttonB
 * Signature: ()Z
 */
JNIEXPORT jint JNICALL Java_com_zoid_mega_bb_Native_buttonB(JNIEnv *, jclass);

/*
 * Class:     com_zoid_mega_bb_Native
 * Method:    buttonBlong
 * Signature: ()Z
 */
JNIEXPORT jint JNICALL Java_com_zoid_mega_bb_Native_buttonBlong(JNIEnv *, jclass);

/*
 * Class:     com_zoid_mega_bb_Native
 * Method:    buttonC
 * Signature: ()Z
 */
JNIEXPORT jint JNICALL Java_com_zoid_mega_bb_Native_buttonC(JNIEnv *, jclass);

/*
 * Class:     com_zoid_mega_bb_Native
 * Method:    buttonD
 * Signature: ()Z
 */
JNIEXPORT jint JNICALL Java_com_zoid_mega_bb_Native_buttonD(JNIEnv *, jclass);

/*
 * Class:     com_zoid_mega_bb_Native
 * Method:    buttonDlong
 * Signature: ()Z
 */
JNIEXPORT jint JNICALL Java_com_zoid_mega_bb_Native_buttonDlong(JNIEnv *, jclass);

/*
 * Class:     com_zoid_mega_bb_Native
 * Method:    getField
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_zoid_mega_bb_Native_getField(JNIEnv *, jclass, jint, jint);

/*
 * Class:     com_zoid_mega_bb_Native
 * Method:    getScore
 * Signature: ()Z
 */
JNIEXPORT jint JNICALL Java_com_zoid_mega_bb_Native_getScore(JNIEnv *, jclass);

/*
 * Class:     com_zoid_mega_bb_Native
 * Method:    getView
 * Signature: ()Z
 */
JNIEXPORT jint JNICALL Java_com_zoid_mega_bb_Native_getView(JNIEnv *, jclass);

/*
 * Class:     com_zoid_mega_bb_Native
 * Method:    getNext
 * Signature: ()Z
 */
JNIEXPORT jint JNICALL Java_com_zoid_mega_bb_Native_getNext(JNIEnv *, jclass);

/*
 * Class:     com_zoid_mega_bb_Native
 * Method:    resetGame
 * Signature: ()Z
 */
JNIEXPORT jint JNICALL Java_com_zoid_mega_bb_Native_resetGame(JNIEnv *, jclass);

/*
 * Class:     com_zoid_mega_bb_Native
 * Method:    pauseContinue
 * Signature: ()Z
 */
JNIEXPORT jint JNICALL Java_com_zoid_mega_bb_Native_pauseContinue(JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif
#endif
