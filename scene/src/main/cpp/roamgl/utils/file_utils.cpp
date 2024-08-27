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

