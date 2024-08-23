//
// Created by 龚喜 on 2024/8/18.
//

#ifndef ASSIMPDEMO_ATTACH_JNI_H
#define ASSIMPDEMO_ATTACH_JNI_H

#include <string>
#include <jni/jni.hpp>

extern JavaVM* theJVM;

extern std::string cachePath;
extern std::string dataPath;

bool attach_jni_thread(JavaVM* vm, JNIEnv** env, std::string threadName);
void detach_jni_thread(JavaVM* vm, JNIEnv** env, bool detach);



#endif //ASSIMPDEMO_ATTACH_JNI_H
