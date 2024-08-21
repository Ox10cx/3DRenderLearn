//
// Created by 龚喜 on 1/27/24.
//

#ifndef ASSIMPDEMO_JNIHELPER_H
#define ASSIMPDEMO_JNIHELPER_H

#include "RenderLogger.h"
#include <string>
#include <pthread.h>
#include <jni.h>
#include <vector>
#include <android/asset_manager.h>


class JNIHelper {

public:
    JNIHelper(JNIEnv *env, jobject assetManager, const std::string& pathToInternalDir);


    ~JNIHelper();

    bool ExtractAssetReturnFilename(std::string assetName, std::string &filename,
                                    bool checkIfFileIsAvailable = false);

private:
    mutable pthread_mutex_t m_ThreadMutex;
    std::string m_sApkInternalPath;
    AAssetManager *m_pApkAssetManager;
};

extern JNIHelper *gHelperObject;


#endif //ASSIMPDEMO_JNIHELPER_H
