//
// Created by gongxi on 2024/10/26.
//

#ifndef ASSIMPDEMO_BUCKET_UTILS_H
#define ASSIMPDEMO_BUCKET_UTILS_H

#include "glm/glm_core.h"

namespace roamgl {

#define INVALID_COOR		(double)(1000000.0)
#define MIN_DOUBLE			(double)(0.000000001)

class BucketUtils {
public:
    static glm::vec3 convertPoint(glm::vec3 a);
    static glm::vec3 perp(glm::vec3 a);
    static double mag(glm::vec3 a);
    static glm::vec3 unit(glm::vec3 a);
    static double dist(glm::vec3 a, glm::vec3 b);
    static bool isValid(glm::vec3& a);
    static void setInValid(glm::vec3*pA);

};

}



#endif //ASSIMPDEMO_BUCKET_UTILS_H
