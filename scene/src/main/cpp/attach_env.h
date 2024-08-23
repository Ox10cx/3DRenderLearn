//
// Created by 龚喜 on 2024/8/22.
//

#ifndef ASSIMPDEMO_ATTACH_ENV_H
#define ASSIMPDEMO_ATTACH_ENV_H

#include <jni/jni.hpp>

namespace android {

    class JNIEnvDeleter {
    private:
        jni::JavaVM* vm = nullptr;
        bool detach = false;

    public:
        JNIEnvDeleter() = default;
        JNIEnvDeleter(jni::JavaVM& v, bool d)
                : vm(&v), detach(d) {}

        void operator()(jni::JNIEnv* p) const {
            if (p && detach) {
                assert(vm);
                vm->DetachCurrentThread();
            }
        }
    };

    using UniqueEnv = std::unique_ptr<jni::JNIEnv, JNIEnvDeleter>;

    UniqueEnv AttachEnv();

}


#endif //ASSIMPDEMO_ATTACH_ENV_H
