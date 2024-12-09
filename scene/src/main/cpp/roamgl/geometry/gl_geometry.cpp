//
// Created by 龚喜 on 2024/8/23.
//

#include "gl_geometry.h"
#include "utils/log.h"

namespace roamgl
{

Geometry::Geometry() {
    m_pLineBucket = new LineBucket(1.0, 1);
}

Geometry::~Geometry() {
    GLCall(glDeleteVertexArrays(1, &mVao));
    GLCall(glDeleteBuffers(1, &mPosVbo));
    GLCall(glDeleteBuffers(1, &mDataVbo));
    GLCall(glDeleteBuffers(1, &mNormalVbo));
    GLCall(glDeleteBuffers(1, &mDirVbo));
    GLCall(glDeleteBuffers(1, &mUvVbo));
    GLCall(glDeleteBuffers(1, &mEbo));


    unsigned int mDataVbo {0};
    unsigned int mNormalVbo {0};
    unsigned int mDirVbo {0};

    if (m_pLineBucket) {
        delete m_pLineBucket;
    }
}

std::unique_ptr<Geometry> Geometry::createLine6()
{
    auto geometry = std::make_unique<Geometry>();

//    unsigned short posNormal[] = {
//            2, 0,
//            2, 1,
//            0, 0,
//            0, 1,
//            0, 2,
//            0, 3,
//    };


    float datas[] = {
            2, 0,128.00000,  65.00000,    1.00000, 0.00000,
            2, 1,128.00000, 191.00000,    1.00000, 0.00000,
            0, 0,65.00000, 65.00000,   1.0, 0.0,
            0, 1,191.00000,  191.00000,   1.0,  0.0,
            0, 2,65.00000, 128.00000,  5.0,   0.0,
            0, 3,191.00000, 128.00000,  5.0, 0.0,
    };



    unsigned short indices[] = {
            0, 1, 2,
            1, 2, 3,
            2, 3, 4,
            3, 4, 5,
    };

    geometry->mIndicesCount = sizeof(indices) / sizeof(unsigned short);;

//    unsigned int& posVbo = geometry->mPosVbo;
//    GLCall(glGenBuffers(1, &posVbo));
//    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
//    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(posNormal), posNormal, GL_STATIC_DRAW));

    unsigned int& dataVbo = geometry->mDataVbo;
    GLCall(glGenBuffers(1, &dataVbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, dataVbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(datas), datas, GL_STATIC_DRAW));


    unsigned int& ebo = geometry->mEbo;
    GLCall(glGenBuffers(1, &ebo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    // 生成VAO
    unsigned int& vao = geometry->mVao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, dataVbo));
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, dataVbo));
    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(2 * sizeof (float ))));


    //绑定EBO
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));

    //解绑VAO
    GLCall(glBindVertexArray(0));

    return geometry;

}

std::unique_ptr<Geometry> Geometry::createLine5()
{
    auto geometry = std::make_unique<Geometry>();

//    unsigned short posNormal[] = {
//            2, 0,
//            2, 1,
//            0, 0,
//            0, 1,
//            0, 2,
//            0, 3,
//    };


    float datas[] = {
            2, 0, 128, 65, 1, 0,
            2, 1, 128, 191, 1, 0,
            0, 0, 128, 65, 1, 0,
            0, 1, 191, 191, 2, 0,
            0, 0, 104, 70,  1,0,
            0, 0, 83,  83,1, 0,
            0, 0, 70, 104,1, 0,
            0, 0, 65, 128,1, 0,
            0, 1, 191, 191, 0,0,
            0, 2, 65, 128, 5, 0,
            0, 3, 191,128, 5, 0,
    };



    unsigned int indices[] = {
            0, 1, 2,
            1, 2, 3,
            2, 3, 4,
            4, 3, 5,
            5, 3, 6,
            6, 3, 7,
            3, 7, 8,
            7, 8, 9,
            8, 9, 10,
    };

    geometry->mIndicesCount = sizeof(indices) / sizeof(unsigned int);;

//    unsigned int& posVbo = geometry->mPosVbo;
//    GLCall(glGenBuffers(1, &posVbo));
//    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
//    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(posNormal), posNormal, GL_STATIC_DRAW));

    unsigned int& dataVbo = geometry->mDataVbo;
    GLCall(glGenBuffers(1, &dataVbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, dataVbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(datas), datas, GL_STATIC_DRAW));


    unsigned int& ebo = geometry->mEbo;
    GLCall(glGenBuffers(1, &ebo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    // 生成VAO
    unsigned int& vao = geometry->mVao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, dataVbo));
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, dataVbo));
    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(2 * sizeof (float ))));


    //绑定EBO
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));

    //解绑VAO
    GLCall(glBindVertexArray(0));

    return geometry;

}

std::unique_ptr<Geometry> Geometry::createLine4()
{
    auto geometry = std::make_unique<Geometry>();


    float poses[] = {
            1.00000, 0.00000,
            1.00000, 0.00000,
            0.00000, 0.00000,
            0.00000, 0.00000,
            0.00000, 1.00000,
            0.00000, 1.00000
    };

    float datas[] = {
            2.00000, 0.00000,
            2.00000, 1.00000,
            0.00000, 0.00000,
            0.00000,  1.00000,
            0.00000, 2.00000,
            0.00000, 3.00000,
    };

    float normales[] = {
            128.00000,  65.00000,
            128.00000, 191.00000,
            65.00000, 65.00000,
            191.00000,  191.00000,
            65.00000, 128.00000,
            191.00000, 128.00000,
    };

    float dires[] = {
            1.00000, 0.00000,
            1.00000, 0.00000,
            1.0, 0.0,
            1.0,  0.0,
            5.0,   0.0,
            5.0, 0.0,
    };

    unsigned short indices[] = {
            0, 1, 2,
            1, 2, 3,
            2, 3, 4,
            3, 4, 5,
    };

    geometry->mIndicesCount = sizeof(indices) / sizeof(unsigned short);

    unsigned int& posVbo = geometry->mPosVbo;
    GLCall(glGenBuffers(1, &posVbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(poses), poses, GL_STATIC_DRAW));

    unsigned int& dataVbo = geometry->mDataVbo;
    GLCall(glGenBuffers(1, &dataVbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, dataVbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(datas), datas, GL_STATIC_DRAW));

    unsigned int& normalVbo = geometry->mNormalVbo;
    GLCall(glGenBuffers(1, &normalVbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, normalVbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(normales), normales, GL_STATIC_DRAW));

    unsigned int& dirVbo = geometry->mDirVbo;
    GLCall(glGenBuffers(1, &dirVbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, dirVbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(dires), dires, GL_STATIC_DRAW));


    unsigned int& ebo = geometry->mEbo;
    GLCall(glGenBuffers(1, &ebo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    // 生成VAO
    unsigned int& vao = geometry->mVao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, dataVbo));
    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, normalVbo));
    GLCall(glEnableVertexAttribArray(2));
    GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, dirVbo));
    GLCall(glEnableVertexAttribArray(3));
    GLCall(glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0));

    //绑定EBO
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));

    //解绑VAO
    GLCall(glBindVertexArray(0));

    return geometry;
}


std::unique_ptr<Geometry> Geometry::createLine3()
{
    auto geometry = std::make_unique<Geometry>();


    float poses[] = {
            0.00000, 0.00000,
            0.00000, 0.00000,
            50.00000, 0.00000,
            50.00000, 0.00000,
            50.00000, 50.00000,
            50.00000, 50.00000
    };

    float datas[] = {
            0.00000, 0.00000,
            0.00000,  1.00000,
            100.00000, 0.00000,
            100.00000, 1.00000,
            100.00000, 100.00000,
            100.00000, 101.00000,
    };

    float normales[] = {
            128.00000, 191.00000,
            128.00000,  65.00000,
            65.00000,  191.00000,
            191.00000, 65.00000,
            65.00000, 128.00000,
            191.00000, 128.00000
    };

    float dires[] = {
            1.0,  0.0,
            1.0,  0.0,
            101.0, 0.0,
            101.0,  0.0,
            201.0,   0.0,
            201.0, 0.0,
    };

    unsigned int indices[] = {
            0, 1, 2,
            1, 2, 3,
            2, 3, 4,
            3, 4, 5,
    };

    geometry->mIndicesCount = sizeof(indices) / sizeof(unsigned int);;

    unsigned int& posVbo = geometry->mPosVbo;
    GLCall(glGenBuffers(1, &posVbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(poses), poses, GL_STATIC_DRAW));

    unsigned int& dataVbo = geometry->mDataVbo;
    GLCall(glGenBuffers(1, &dataVbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, dataVbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(datas), datas, GL_STATIC_DRAW));

    unsigned int& normalVbo = geometry->mNormalVbo;
    GLCall(glGenBuffers(1, &normalVbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, normalVbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(normales), normales, GL_STATIC_DRAW));

    unsigned int& dirVbo = geometry->mDirVbo;
    GLCall(glGenBuffers(1, &dirVbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, dirVbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(dires), dires, GL_STATIC_DRAW));


    unsigned int& ebo = geometry->mEbo;
    GLCall(glGenBuffers(1, &ebo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    // 生成VAO
    unsigned int& vao = geometry->mVao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, dataVbo));
    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, normalVbo));
    GLCall(glEnableVertexAttribArray(2));
    GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, dirVbo));
    GLCall(glEnableVertexAttribArray(3));
    GLCall(glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0));

    //绑定EBO
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));

    //解绑VAO
    GLCall(glBindVertexArray(0));

    return geometry;
}



std::unique_ptr<Geometry> Geometry::createLine2()
{
    auto geometry = std::make_unique<Geometry>();

    GeometryCoordinates coordinates;
    coordinates.push_back({1, 0});
    coordinates.push_back({0, 0});
    coordinates.push_back({0, 1});

    LineBucket* lineBucket = geometry->m_pLineBucket;
    lineBucket->addGeometry(coordinates);

    gfx::VertexVector<LineLayoutVertex> vertices = lineBucket->vertices;
    gfx::IndexVector<gfx::Triangles> triangles = lineBucket->triangles;

    geometry->mIndicesCount = triangles.elements();

    unsigned int& posVbo = geometry->mPosVbo;
    GLCall(glGenBuffers(1, &posVbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.bytes(), vertices.data(), GL_STATIC_DRAW));


    unsigned int& ebo = geometry->mEbo;
    GLCall(glGenBuffers(1, &ebo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.bytes(), triangles.data(), GL_STATIC_DRAW));

    // 生成VAO
    unsigned int& vao = geometry->mVao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, vertices.bytes() / vertices.elements(), (void *)0));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_FALSE, vertices.bytes() / vertices.elements(), (void *) (2 * sizeof (short))));

    //绑定EBO
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));

    //解绑VAO
    GLCall(glBindVertexArray(0));

    return geometry;
}

std::unique_ptr<Geometry> Geometry::createLine()
{
    auto geometry = std::make_unique<Geometry>();

    GeometryCoordinates coordinates;
    coordinates.push_back({0, 0});
    coordinates.push_back({50, 0});
//    coordinates.push_back({2768, 5020});
//    coordinates.push_back({2224, 6624});
//    coordinates.push_back({1431, 10240});


    LineBucket* lineBucket = geometry->m_pLineBucket;
    lineBucket->addGeometry(coordinates);

    gfx::VertexVector<LineLayoutVertex> vertices = lineBucket->vertices;
    gfx::IndexVector<gfx::Triangles> triangles = lineBucket->triangles;

    int l = vertices.bytes();
    int n = triangles.bytes();
    int stride = vertices.bytes() / vertices.elements();
    int b = sizeof (unsigned char);

    unsigned int& posVbo = geometry->mPosVbo;
    GLCall(glGenBuffers(1, &posVbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.bytes(), vertices.data(), GL_STATIC_DRAW));

    unsigned int& ebo = geometry->mEbo;
    GLCall(glGenBuffers(1, &ebo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, ebo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, triangles.bytes(), triangles.data(), GL_STATIC_DRAW));

    // 生成VAO
    unsigned int& vao = geometry->mVao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));


    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, vertices.bytes() / vertices.elements(), (void *)0));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_FALSE, vertices.bytes() / vertices.elements() , (void *) (2 * sizeof (short ))));

    //绑定EBO
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));

    //解绑VAO
    GLCall(glBindVertexArray(0));

    geometry->mIndicesCount = triangles.elements();



////    layout(location = 0) in vec2 a_pos_normal;
////    layout(location = 1) in vec4 a_data;


    //    float vertices2[] = {
//             0.50000, 0.50000,0.00000, 0.70711, -0.70711, 0.00000 , 0.00000,
//             0.50000, 0.50000, 0.00000, -0.70711, 0.70711,0.00000, 0.00000,
//             -0.50000, -0.50000,0.00000, 0.70711, -0.70711,0.00000, 0.00000,
//             -0.50000, -0.50000,0.00000, -0.70711, 0.70711,0.00000, 0.00000,
//     };

//    unsigned int& posVbo = geometry->mPosVbo;
//    GLCall(glGenBuffers(1, &posVbo));
//    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
//    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW));

//
//
////    std::vector<glm::vec3> vertices;
////    vertices.push_back(glm::vec3 (0,   0.25, 0.0f));
////    vertices.push_back(glm::vec3 (0, -0.25, 0.0f));
//
//
//
////    lineBucket->addGeometry(vertices, 600 / 2.0);
//
////    std::vector<glm::vec3>& poses = lineBucket->getPos();
////    std::vector<glm::vec4>& dataes = lineBucket->getData();
////    std::vector<glm::vec3>& normales = lineBucket->getNormal();
////    std::vector<glm::vec2>& dires = lineBucket->getDir();
////    std::vector<int>& indexes = lineBucket->getIndexBuffer();
//
//     float vertices[] = {
//             0.50000, 0.50000,0.00000, 0.70711, -0.70711, 0.00000 , 0.00000,
//             0.50000, 0.50000, 0.00000, -0.70711, 0.70711,0.00000, 0.00000,
//             -0.50000, -0.50000,0.00000, 0.70711, -0.70711,0.00000, 0.00000,
//             -0.50000, -0.50000,0.00000, -0.70711, 0.70711,0.00000, 0.00000,
//     };
//
//
////    std::vector<glm::vec3> poses;
////    poses.push_back(glm::vec3 (0.50000, 0.50000,0.00000));
////    poses.push_back(glm::vec3 (0.50000, 0.50000, 0.00000));
////    poses.push_back(glm::vec3 (-0.50000, -0.50000,0.00000));
////    poses.push_back(glm::vec3 (-0.50000, -0.50000,0.00000));
////
////    std::vector<glm::vec4> dataes;
////    dataes.push_back(glm::vec4 (0.70711, -0.70711, 0.00000 , 0.00000));
////    dataes.push_back(glm::vec4 (-0.70711, 0.70711,0.00000, 0.00000));
////    dataes.push_back(glm::vec4 (0.70711, -0.70711,0.00000, 0.00000));
////    dataes.push_back(glm::vec4 (-0.70711, 0.70711,0.00000, 0.00000));
//
//    std::vector<glm::vec3> normales;
//    normales.push_back(glm::vec3 (0.00000, 0.00000, 0.00000));
//    normales.push_back(glm::vec3 (0.00000, 0.00000,1.00000));
//    normales.push_back(glm::vec3 (0.00000, 0.00000, 0.00000));
//    normales.push_back(glm::vec3 (0.00000, 0.00000,1.00000));
//
//    std::vector<glm::vec2> dires;
//    dires.push_back(glm::vec2 (1.00000, 0.00000));
//    dires.push_back(glm::vec2 (1.00000, 0.00000));
//    dires.push_back(glm::vec2 (1.00000, 0.00000));
//    dires.push_back(glm::vec2 (1.00000, 0.00000));
//
//
//    unsigned int indices[] = {
//            0, 1, 2,
//            1, 2, 3
//    };
//
//    unsigned int& posVbo = geometry->mPosVbo;
//    GLCall(glGenBuffers(1, &posVbo));
//    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
//    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
//
//
//    // 生成VBO
////    unsigned int& posVbo = geometry->mPosVbo;
////    GLCall(glGenBuffers(1, &posVbo));
////    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
////    GLCall(glBufferData(GL_ARRAY_BUFFER, poses.size() * sizeof(float) * 3, poses.data(), GL_STATIC_DRAW));
//
////    unsigned int& dataVbo = geometry->mDataVbo;
////    GLCall(glGenBuffers(1, &dataVbo));
////    GLCall(glBindBuffer(GL_ARRAY_BUFFER, dataVbo));
////    GLCall(glBufferData(GL_ARRAY_BUFFER, dataes.size() * sizeof(float) * 4, dataes.data(), GL_STATIC_DRAW));
//
//    unsigned int& normalVbo = geometry->mNormalVbo;
//    GLCall(glGenBuffers(1, &normalVbo));
//    GLCall(glBindBuffer(GL_ARRAY_BUFFER, normalVbo));
//    GLCall(glBufferData(GL_ARRAY_BUFFER, normales.size() * sizeof(float) * 3, normales.data(), GL_STATIC_DRAW));
//
//    unsigned int& dirVbo = geometry->mDirVbo;
//    GLCall(glGenBuffers(1, &dirVbo));
//    GLCall(glBindBuffer(GL_ARRAY_BUFFER, dirVbo));
//    GLCall(glBufferData(GL_ARRAY_BUFFER, dires.size() * sizeof(float) * 2, dires.data(), GL_STATIC_DRAW));
//
//    unsigned int& ebo = geometry->mEbo;
//    GLCall(glGenBuffers(1, &ebo));
//    GLCall(glBindBuffer(GL_ARRAY_BUFFER, ebo));
//    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));
//
//    // 生成VAO
//    unsigned int& vao = geometry->mVao;
//    GLCall(glGenVertexArrays(1, &vao));
//    GLCall(glBindVertexArray(vao));
//
//    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
//    GLCall(glEnableVertexAttribArray(0));
//    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)0));
//
//    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
//    GLCall(glEnableVertexAttribArray(1));
//    GLCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *) (3 * sizeof(float))));
//
//
//
//
////    GLCall(glBindBuffer(GL_ARRAY_BUFFER, dataVbo));
////    GLCall(glEnableVertexAttribArray(1));
////    GLCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0));
//
//    GLCall(glBindBuffer(GL_ARRAY_BUFFER, normalVbo));
//    GLCall(glEnableVertexAttribArray(2));
//    GLCall(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0));
//
//    GLCall(glBindBuffer(GL_ARRAY_BUFFER, dirVbo));
//    GLCall(glEnableVertexAttribArray(3));
//    GLCall(glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0));
//
//
//    //绑定EBO
//    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
//
//    //解绑VAO
//    GLCall(glBindVertexArray(0));
//
//
////    std::vector<glm::vec3> posDst;
////    std::vector<glm::vec4> dataDst;
////    std::vector<glm::vec3> normalDst;
////    std::vector<glm::vec2> dirDst;
//
////    for (int i = 0; i < indexes.size(); i++) {
////        if(indexes[i] >= poses.size())
////        {
////            Log::Info(roamgl::Event::Render, "DrawCarToCenterPath index is too large");
////            return nullptr;
////        }
////        Log::Info(roamgl::Event::Render, "createLine indexes [%d]", indexes[i]);
////
////        Log::Info(roamgl::Event::Render, "createLine posDst [%.5f, %.5f, %.5f]", poses[indexes[i]].x, poses[indexes[i]].y, poses[indexes[i]].z);
////        Log::Info(roamgl::Event::Render, "createLine dataDst [%.5f, %.5f, %.5f, %.5f]", dataes[indexes[i]].x, dataes[indexes[i]].y, dataes[indexes[i]].z, dataes[indexes[i]].w);
////        Log::Info(roamgl::Event::Render, "createLine normalDst [%.5f, %.5f, %.5f]", normales[indexes[i]].x, normales[indexes[i]].y, normales[indexes[i]].z);
////        Log::Info(roamgl::Event::Render, "createLine dirDst [%.5f, %.5f]", dires[indexes[i]].x, dires[indexes[i]].y);
////
////        posDst.push_back(poses[indexes[i]]);
////        dataDst.push_back(dataes[indexes[i]]);
////        normalDst.push_back(normales[indexes[i]]);
////        dirDst.push_back(dires[indexes[i]]);
////    }

//    geometry->mIndicesCount = 6;

    return geometry;
}


std::unique_ptr<Geometry> Geometry::createPlane(float centerX, float centerY, float width, float height)
{
    auto geometry = std::make_unique<Geometry>();

    geometry->mIndicesCount = 6;

    float halfW = width / 2.0f;
    float halfH = height / 2.0f;

    float positions[] = {
            centerX - halfW, centerX - halfH, 0.0f,
            centerX + halfW, centerX - halfH, 0.0f,
            centerX + halfW, centerX + halfH, 0.0f,
            centerX - halfW, centerX + halfH, 0.0f,
    };

    float uvs[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
    };

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    // 生成VBO
    unsigned int& posVbo = geometry->mPosVbo;
    GLCall(glGenBuffers(1, &posVbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

    unsigned int& uvVbo = geometry->mUvVbo;
    GLCall(glGenBuffers(1, &uvVbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, uvVbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof (uvs), uvs, GL_STATIC_DRAW));

    unsigned int& ebo = geometry->mEbo;
    GLCall(glGenBuffers(1, &ebo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, ebo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    // 生成VAO
    unsigned int& vao = geometry->mVao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));

    // 绑定VBO
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float ) * 3, (void*) 0));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, uvVbo));
    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof (float) * 2, (void*)0));

    //绑定EBO
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));

    //解绑VAO
    GLCall(glBindVertexArray(0));

    return geometry;
}

std::unique_ptr<Geometry> Geometry::createPlane(std::vector<float> positions)
{
    auto geometry = std::make_unique<Geometry>();

    geometry->mIndicesCount = 6;

    float uvs[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
    };

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    // 生成VBO
    unsigned int& posVbo = geometry->mPosVbo;
    GLCall(glGenBuffers(1, &posVbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_STATIC_DRAW));

    unsigned int& uvVbo = geometry->mUvVbo;
    GLCall(glGenBuffers(1, &uvVbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, uvVbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof (uvs), uvs, GL_STATIC_DRAW));

    unsigned int& ebo = geometry->mEbo;
    GLCall(glGenBuffers(1, &ebo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, ebo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    // 生成VAO
    unsigned int& vao = geometry->mVao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));

    // 绑定VBO
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float ) * 3, (void*) 0));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, uvVbo));
    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof (float) * 2, (void*)0));

    //绑定EBO
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));

    //解绑VAO
    GLCall(glBindVertexArray(0));

    return geometry;
}


//Geometry *Geometry::createBox(float size) {
////    Geometry *geomerty = new Geometry();
////
////    float halfSize = size / 2.0f;
////    float positions[] = {
////            -halfSize, -halfSize, -halfSize,   // 左下后
////            halfSize, -halfSize, -halfSize,   // 右下后
////            halfSize,  halfSize, -halfSize,   // 右上后
////            -halfSize,  halfSize, -halfSize,   // 左上后
////            -halfSize, -halfSize,  halfSize,   // 左下前
////            halfSize, -halfSize,  halfSize,   // 右下前
////            halfSize,  halfSize,  halfSize,   // 右上前
////            -halfSize,  halfSize,  halfSize,   // 左上前
////    };
////
////    float uvs[] = {
////            0.0f, 0.0f,
////            1.0f, 0.0f,
////            1.0f, 1.0f,
////            0.0f, 1.0f,
////
////            0.0f, 1.0f,
////            1.0f, 1.0f,
////            0.0f, 0.0f,
////            1.0f, 0.0f,
////    };
////
////    // 立方体索引数据
////    unsigned int indices[] = {
////            // 后面
////            0, 1, 2,
////            2, 3, 0,
////            // 前面
////            4, 5, 6,
////            6, 7, 4,
////            // 左面
////            0, 4, 7,
////            7, 3, 0,
////            // 右面
////            1, 5, 6,
////            6, 2, 1,
////            // 底面
////            0, 1, 5,
////            5, 4, 0,
////            // 顶面
////            3, 2, 6,
////            6, 7, 3
////    };
////
////    geomerty->mIndicesCount = sizeof (indices) / sizeof (unsigned int);
//
//
//
//}

}


