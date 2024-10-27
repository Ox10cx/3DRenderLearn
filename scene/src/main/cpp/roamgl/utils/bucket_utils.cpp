//
// Created by gongxi on 2024/10/26.
//

#include "bucket_utils.h"

namespace roamgl {

glm::vec3 BucketUtils::convertPoint(glm::vec3 a)
{
    return glm::vec3(a.x, a.y, a.z);
}

glm::vec3 BucketUtils::perp(glm::vec3 a)
{
    return glm::vec3(-a.z, 0, a.x);
}

double BucketUtils::mag(glm::vec3 a)
{
    return sqrt(a.x * a.x + a.z * a.z);
}

glm::vec3 BucketUtils::unit(glm::vec3 a)
{
    double magnitude = mag(a);
    if (magnitude == 0.0) {
        return glm::vec3(a.x, a.y, a.z);
    }
    return glm::vec3(a.x / magnitude, a.y/ magnitude, a.z / magnitude);
}

double BucketUtils::dist(glm::vec3 a, glm::vec3 b)
{
    double dx = b.x - a.x;
    double dz = b.z - a.z;
    double c = sqrt(dx * dx + dz * dz);
    return c;
}

bool BucketUtils::isValid(glm::vec3& a)
{
    return (abs(a.y - INVALID_COOR) > MIN_DOUBLE);
}

void BucketUtils::setInValid(glm::vec3* pA)
{
    pA->x = INVALID_COOR;
    pA->y = INVALID_COOR;
    pA->z = INVALID_COOR;
}


}
