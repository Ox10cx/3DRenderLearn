//
// Created by 龚喜 on 1/27/24.
//

#ifndef ASSIMPDEMO_ASSIMPLOADER_H
#define ASSIMPDEMO_ASSIMPLOADER_H


#include <map>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "GLFunctions.h"
#include "GLM.h"

// info used to render a mesh
struct MeshInfo {
    GLuint  m_nTextureIndex;
    int     m_nNumberOfFaces;
    GLuint  m_nFaceBuffer;
    GLuint  m_nVertexBuffer;
    GLuint  m_nTextureCoordBuffer;
};

class AssimpLoader {

public:
    AssimpLoader();
    ~AssimpLoader();

    void Render3DModel(glm::mat4 *MVP);
    bool Load3DModel(const std::string& modelFilename);
    void Delete3DModel();

private:
    void GenerateGLBuffers();
    bool LoadTexturesToGL(const std::string& modelFilename);

    std::vector<MeshInfo> mModelMeshes;       // contains one struct for every mesh in model
    Assimp::Importer *m_pImporterPtr;
    const aiScene* m_pAiScene;                           // assimp's output data structure
    bool m_bObjectLoaded;

    std::map<std::string, GLuint> mTextureNameMap;   // (texture filename, texture name in GL)

    GLuint  m_nVertexAttribute, m_nVertexUVAttribute;     // attributes for shader variables
    GLuint  m_nShaderProgramID;
    GLint   m_MvpLocation, m_TextureSamplerLocation;    // location of MVP in the shader
};

#endif //ASSIMPLOADER_H
