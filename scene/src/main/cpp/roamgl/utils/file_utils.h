//
// Created by 龚喜 on 2024/8/26.
//

#ifndef ASSIMPDEMO_FILE_UTILS_H
#define ASSIMPDEMO_FILE_UTILS_H

#include <string>
#include <android/asset_manager.h>

class FileUtils {
public:
    static bool ExtractAssetReturnFilename(AAssetManager* assetManage, const std::string& fullPath,
                                           const std::string& assetPath, bool checkIfFileIsAvailable = false);
    static std::string GetFileName(const std::string& fileName);

};


#endif //ASSIMPDEMO_FILE_UTILS_H
