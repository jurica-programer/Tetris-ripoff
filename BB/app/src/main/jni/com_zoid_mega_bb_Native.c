#include "com_zoid_mega_bb_Native.h"
#include <stdio.h>
#include <pthread.h>


static JavaVM *cached_jvm;
static jclass globalClazCallbacks;

//TODO prouči ovaj kod
// This function is used for sending end of playback and trick mode and seek enabled callbacks to java.
int sendCallback(int callbackValue)
{
    JNIEnv * env;
    jmethodID methodIDForCallback;
    int attached = 0;
    jint getEnvRes;

    getEnvRes = (*cached_jvm)->GetEnv(cached_jvm, (void**) &env, JNI_VERSION_1_4);

    switch (getEnvRes)
    {
        case JNI_OK:
            break;
        case JNI_EDETACHED:
            if ((*cached_jvm)->AttachCurrentThread(cached_jvm, &env, NULL) != 0)
            {
                return 0;
            }
            attached = 1;
            break;
        case JNI_EVERSION:
            return 0;
    }

    methodIDForCallback = (*env)->GetStaticMethodID(env, globalClazCallbacks, "callback", "(I)V");
    if (methodIDForCallback == NULL)
    {
        if (attached)
        {
            (*cached_jvm)->DetachCurrentThread(cached_jvm);
        }
        return 0;
    }

    (*env)->CallStaticVoidMethod(env, globalClazCallbacks, methodIDForCallback, (jint) callbackValue);

    if ((*env)->ExceptionCheck(env))
    {
        (*env)->ExceptionDescribe(env);
    }

    if (attached)
    {
        (*cached_jvm)->DetachCurrentThread(cached_jvm);
    }
    return 1;
}

int sendButtonCallback(int callbackValue)
{
    JNIEnv * env;
    jmethodID methodIDForCallback;
    int attached = 0;
    jint getEnvRes;

    getEnvRes = (*cached_jvm)->GetEnv(cached_jvm, (void**) &env, JNI_VERSION_1_4);

    switch (getEnvRes)
    {
        case JNI_OK:
            break;
        case JNI_EDETACHED:
            if ((*cached_jvm)->AttachCurrentThread(cached_jvm, &env, NULL) != 0)
            {
                return 0;
            }
            attached = 1;
            break;
        case JNI_EVERSION:
            return 0;
    }

    methodIDForCallback = (*env)->GetStaticMethodID(env, globalClazCallbacks, "callbackButton", "(Z)V");
    if (methodIDForCallback == NULL)
    {
        if (attached)
        {
            (*cached_jvm)->DetachCurrentThread(cached_jvm);
        }
        return 0;
    }

    (*env)->CallStaticVoidMethod(env, globalClazCallbacks, methodIDForCallback, (jboolean) callbackValue);

    if ((*env)->ExceptionCheck(env))
    {
        (*env)->ExceptionDescribe(env);
    }

    if (attached)
    {
        (*cached_jvm)->DetachCurrentThread(cached_jvm);
    }
    return 1;
}


//TODO prouči ovaj kod
jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;
    cached_jvm = vm;
    jclass claz;

    if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK)
    {
        return 0;
    }

    claz = (*env)->FindClass(env, "com/zoid/mega/bb/Native");

    if (claz != NULL)
    {
        globalClazCallbacks = (jclass)(*env)->NewGlobalRef(env, claz);
    }
    return JNI_VERSION_1_4;
}

JNIEXPORT jint Java_com_zoid_mega_bb_Native_startThread(JNIEnv * env, jclass klasa){
    startThread();
    return 1;
};

JNIEXPORT jint Java_com_zoid_mega_bb_Native_startButton(JNIEnv * env, jclass klasa, jint state){
    timerTrigger(state);
    return 1;
};

JNIEXPORT jint Java_com_zoid_mega_bb_Native_initGameRes(JNIEnv * env, jclass klasa){
    init_game_res();
    return 1;
};

JNIEXPORT jint Java_com_zoid_mega_bb_Native_terminateGameRes(JNIEnv * env, jclass klasa){
    enqueue(terminate_game_res, NO_DATA, no_type);
    return 1;
};

JNIEXPORT jint Java_com_zoid_mega_bb_Native_buttonA(JNIEnv * env, jclass klasa){
    enqueue(move_block, MOVE_LEFT, integer_t);
    return 1;
};

JNIEXPORT jint Java_com_zoid_mega_bb_Native_buttonAlong(JNIEnv * env, jclass klasa){
    enqueue(move_block, MOVE_LEFT, integer_t);
    enqueue(move_block, MOVE_LEFT, integer_t);
    enqueue(move_block, MOVE_LEFT, integer_t);
    enqueue(move_block, MOVE_LEFT, integer_t);
    enqueue(move_block, MOVE_LEFT, integer_t);
    enqueue(move_block, MOVE_LEFT, integer_t);
    enqueue(move_block, MOVE_LEFT, integer_t);
    enqueue(move_block, MOVE_LEFT, integer_t);
    enqueue(move_block, MOVE_LEFT, integer_t);
    return 1;
};

JNIEXPORT jint Java_com_zoid_mega_bb_Native_buttonB(JNIEnv * env, jclass klasa){
    enqueue(block_fall, NO_DATA, no_type);
    return 1;
};

JNIEXPORT jint Java_com_zoid_mega_bb_Native_buttonBlong(JNIEnv * env, jclass klasa){
    enqueue(slam_block, NO_DATA, no_type);
    return 1;
};

JNIEXPORT jint Java_com_zoid_mega_bb_Native_buttonC(JNIEnv * env, jclass klasa){
    enqueue(rotate_block, NO_DATA, no_type);
    return 1;
};

JNIEXPORT jint Java_com_zoid_mega_bb_Native_buttonD(JNIEnv * env, jclass klasa){
    enqueue(move_block, MOVE_RIGHT, integer_t);
    return 1;
};

JNIEXPORT jint Java_com_zoid_mega_bb_Native_buttonDlong(JNIEnv * env, jclass klasa){
    enqueue(move_block, MOVE_RIGHT, integer_t);
    enqueue(move_block, MOVE_RIGHT, integer_t);
    enqueue(move_block, MOVE_RIGHT, integer_t);
    enqueue(move_block, MOVE_RIGHT, integer_t);
    enqueue(move_block, MOVE_RIGHT, integer_t);
    enqueue(move_block, MOVE_RIGHT, integer_t);
    enqueue(move_block, MOVE_RIGHT, integer_t);
    enqueue(move_block, MOVE_RIGHT, integer_t);
    enqueue(move_block, MOVE_RIGHT, integer_t);
    return 1;
};

JNIEXPORT jboolean Java_com_zoid_mega_bb_Native_getField(JNIEnv * env, jclass klasa, jint row, jint column){
    return getFieldValue(row, column);
};

JNIEXPORT jint Java_com_zoid_mega_bb_Native_getScore(JNIEnv * env, jclass klasa){
    return getScoreValue();
};

JNIEXPORT jint Java_com_zoid_mega_bb_Native_getView(JNIEnv * env, jclass klasa){
    return getView();
};

JNIEXPORT jint Java_com_zoid_mega_bb_Native_getNext(JNIEnv * env, jclass klasa){
    return getNextBlock();
};

JNIEXPORT jint Java_com_zoid_mega_bb_Native_resetGame(JNIEnv * env, jclass klasa){
    return resetGame();
};

JNIEXPORT jint Java_com_zoid_mega_bb_Native_pauseContinue(JNIEnv * env, jclass klasa){
    enqueue(pauseContinue, NO_DATA, no_type);
    return 1;
};