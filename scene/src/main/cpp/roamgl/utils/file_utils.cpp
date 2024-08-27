//
// Created by 龚喜 on 2024/8/26.
//

#include "file_utils.h"
#include "log.h"

std::string FileUtils::GetFileName(const std::string& fileName)
{
    // assume filename is of the form "<path>/<name>.<type>"
    std::string::size_type slashIndex = fileName.find_last_of("/");

    std::string onlyName;
    if (slashIndex == std::string::npos) {
        onlyName = fileName.substr(0, std::string::npos);
    } else {
        onlyName = fileName.substr(slashIndex + 1, std::string::npos);
    }

    return onlyName;
}

 bool FileUtils::ExtractAssetReturnFilename(AAssetManager* assetManage, const std::string& fullPath,
                                            const std::string& assetPath, bool checkIfFileIsAvailable)
{
    FILE* file = fopen(fullPath.c_str(), "rb");
    if (file && checkIfFileIsAvailable) {
        Log::Info(Event::File, "Found extracted file in assets: %s", fullPath.c_str());
        fclose(file);
        return true;
    }

    bool result = false;
    AAsset* asset = AAssetManager_open(assetManage, assetPath.c_str(), AASSET_MODE_STREAMING);

    char buf[BUFSIZ];
    int nb_read = 0;
    if (asset != NULL)
    {
        FILE* out = fopen(fullPath.c_str(), "w");
        while ((nb_read = AAsset_read(asset, buf, BUFSIZ)) > 0)
        {
            fwrite(buf, nb_read, 1, out);
        }
        fclose(out);
        AAsset_close(asset);
        result = true;
        Log::Info(Event::File, "Asset extracted: %s", fullPath.c_str());
    }
    else
    {
        Log::Error(Event::File, "Asset not found: %s", assetPath.c_str());
    }
    return result;

}

//bool FileUtils::ExtractAssetReturnFilename(AAssetManager* assetManage, const std::string& assetName, std::string& filename,
//                                       bool checkIfFileIsAvailable)
//{
////    // construct the filename in internal storage by concatenating with path to internal storage
////    filename = m_sApkInternalPath + "/" + GetFileName(assetName);
////
////    // check if the file was previously extracted and is available in app's internal dir
////    FILE* file = fopen(filename.c_str(), "rb");
////    if (file && checkIfFileIsAvailable) {
////        LOGI("Found extracted file in assets: %s", filename.c_str());
////        fclose(file);
////        pthread_mutex_unlock(&m_ThreadMutex);
////        return true;
////
////    }
////
////    // let us look for the file in assets
////    bool result = false;
////
////    // AAsset objects are not thread safe and need to be protected with mutex
////    pthread_mutex_lock(&m_ThreadMutex);
////
////    // Open file
////    AAsset* asset = AAssetManager_open(m_pApkAssetManager, assetName.c_str(), AASSET_MODE_STREAMING);
////
////    char buf[BUFSIZ];
////    int nb_read = 0;
////    if (asset != NULL)
////    {
////        FILE* out = fopen(filename.c_str(), "w");
////        while ((nb_read = AAsset_read(asset, buf, BUFSIZ)) > 0)
////        {
////            fwrite(buf, nb_read, 1, out);
////        }
////        fclose(out);
////        AAsset_close(asset);
////        result = true;
////
////        LOGI("Asset extracted: %s", filename.c_str());
////    }
////    else
////    {
////        LOGE("Asset not found: %s", assetName.c_str());
////    }
////
////    pthread_mutex_unlock(&m_ThreadMutex);
////    return result;
//
//    return true;
//}
