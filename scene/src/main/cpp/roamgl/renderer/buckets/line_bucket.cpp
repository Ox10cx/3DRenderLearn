//
// Created by gongxi on 2024/10/26.
//

#include "line_bucket.h"
#include <cmath>
#include "utils/bucket_utils.h"

namespace roamgl {

/*
 * Sharp corners cause dashed lines to tilt because the distance along the line
 * is the same at both the inner and outer corners. To improve the appearance of
 * dashed lines we add extra points near sharp corners so that a smaller part
 * of the line is tilted.
 *
 * COS_HALF_SHARP_CORNER controls how sharp a corner has to be for us to add an
 * extra vertex. The default is 75 degrees.
 *
 * The newly created vertices are placed SHARP_CORNER_OFFSET pixels from the corner.
 */
    const float COS_HALF_SHARP_CORNER = cos(75.0 / 2.0 * (M_PI / 180.0));

// The number of bits that is used to store the line distance in the buffer.
    const int LINE_DISTANCE_BUFFER_BITS = 14;

// We don't have enough bits for the line distance as we'd like to have, so
// use this value to scale the line distance (in tile units) down to a smaller
// value. This lets us store longer distances while sacrificing precision.
    const float LINE_DISTANCE_SCALE = 1.0 / 2.0;

// The maximum line distance, in tile units, that fits in the buffer.
    const float MAX_LINE_DISTANCE = pow(2, LINE_DISTANCE_BUFFER_BITS) / LINE_DISTANCE_SCALE;

    const double LineRoundLimit = 2.0;


    int32_t EXTENT = 8192;
    float tileSize = 512;

    int LineLayoutVertex::size() {
        return mPos.size();
    }

    void LineLayoutVertex::add(glm::vec3 p, glm::vec3 e, bool roundX, bool roundY, int8_t dir,
                               int32_t linesofar) {

        int nRoundX = (roundX == true);
        int nRoundY = (roundY == true);
        //LOGI("LineLayoutVertex::add [%f,%f] ", p.x(), p.z());
        mPos.push_back(glm::vec3(p.x, p.y, p.z));
        mNormal.push_back(glm::vec3(nRoundX, nRoundY, 0));
        //mData.push_back(osg::Vec4(extrudeScale * e.x(), 0.0, extrudeScale * e.z(), 0.0));
        mData.push_back(glm::vec4(e.x, e.y, e.z, 0.0));
        mDir.push_back(glm::vec2(((dir == 0 ? 0 : (dir < 0 ? -1 : 1)) + 1), linesofar & 0x3F));

//        int nRoundX = (roundX == true);
//        int nRoundY = (roundY == true);
//        //LOGI("LineLayoutVertex::add [%f,%f] ", p.x(), p.z());
//        mPos.push_back(glm::vec3(p.x, 0, p.z));
//        mNormal.push_back(glm::vec3(nRoundX, 0, nRoundY));
//        //mData.push_back(osg::Vec4(extrudeScale * e.x(), 0.0, extrudeScale * e.z(), 0.0));
//        mData.push_back(glm::vec4(e.x, 0.0, e.z, 0.0));
//        mDir.push_back(glm::vec2(((dir == 0 ? 0 : (dir < 0 ? -1 : 1)) + 1), linesofar & 0x3F));

    }

    std::vector<glm::vec3> &LineLayoutVertex::getPos() {
        return mPos;
    }

    std::vector<glm::vec4> &LineLayoutVertex::getData() {
        return mData;
    }

    std::vector<glm::vec3> &LineLayoutVertex::getNormal() {
        return mNormal;
    }

    std::vector<glm::vec2> &LineLayoutVertex::getDir() {
        return mDir;
    }


    void LineLayoutVertex::reset() {
        mPos.clear();
        mData.clear();
        mNormal.clear();
        mDir.clear();
    }


    LineBucket::LineBucket() {
        overscaling = 1;
        //osg::ref_ptr<osg::DrawElementsUInt> mTriangles = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
    }


    LineBucket::~LineBucket() {
    }


    void LineBucket::addGeometry(const std::vector<glm::vec3> &coordinates, double dHalfHeight) {
        //mTriangles = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
        mTriangles.clear();
        vertices.reset();
        int l = coordinates.size();
        // If the line has duplicate vertices at the end, adjust length to remove them.
        while (l >= 2 && coordinates[l - 1] == coordinates[l - 2]) {
            l--;
        }
        int len = l;

        int i = 0;
        // If the line has duplicate vertices at the start, adjust index to remove them.
        while (i < len - 1 && coordinates[i] == coordinates[i + 1]) {
            i++;
        }
        int first = i;

        // Ignore invalid geometry.
        if (len < 2) {
            return;
        }

        //const float miterLimit = layout.get<LineJoin>() == LineJoinType::Bevel ? 1.05f : float(layout.get<LineMiterLimit>());
        //const double sharpCornerOffset = SHARP_CORNER_OFFSET * (float(EXTENT) / (tileSize * overscaling));
        SHARP_CORNER_OFFSET = (double) 10.0f / dHalfHeight;
        const double sharpCornerOffset = SHARP_CORNER_OFFSET;
        const float miterLimit = 1.05f;
        extrudeScale = 1.0;//(double)63/dHalfHeight;

        const glm::vec3 firstCoordinate = coordinates[first];
        //const int beginCap = LineCapTypeRound;
        //const int endCap = LineCapTypeRound;
        const int beginCap = LineCapTypeButt;
        const int endCap = LineCapTypeButt;

        double distance = 0;
        bool startOfLine = true;
        glm::vec3 currentCoordinate(INVALID_COOR, INVALID_COOR, INVALID_COOR);
        glm::vec3 prevCoordinate(INVALID_COOR, INVALID_COOR, INVALID_COOR);
        glm::vec3 nextCoordinate(INVALID_COOR, INVALID_COOR, INVALID_COOR);
        glm::vec3 prevNormal(INVALID_COOR, INVALID_COOR, INVALID_COOR);
        glm::vec3 nextNormal(INVALID_COOR, INVALID_COOR, INVALID_COOR);

        // the last three vertices added
        e1 = e2 = e3 = -1;

        const int startVertex = vertices.size();
        std::vector<TriangleElement> triangleStore;

        for (int i = first; i < len; ++i) {
            if (i + 1 < len) {
                // just the next vertex
                nextCoordinate = coordinates[i + 1];
            } else {
                // there is no next vertex
                BucketUtils::setInValid(&nextCoordinate);
            }

            //LOGI("addGeometry nextCoordinate	[ %f,%f] [ %f,%f] %d", coordinates[i].x(), coordinates[i].z(),	nextCoordinate.x(), nextCoordinate.z(), i);

            // if two consecutive vertices exist, skip the current one
            if (BucketUtils::isValid(nextCoordinate) && coordinates[i] == nextCoordinate) {
                continue;
            }

            if (BucketUtils::isValid(nextNormal)) {
                prevNormal.x = nextNormal.x;
                prevNormal.y = nextNormal.y;
                prevNormal.z = nextNormal.z;
            }
            if (BucketUtils::isValid(currentCoordinate)) {
                prevCoordinate.x = currentCoordinate.x;
                prevCoordinate.y = currentCoordinate.y;
                prevCoordinate.z = currentCoordinate.z;
            }
            currentCoordinate = coordinates[i];

            // Calculate the normal towards the next vertex in this line. In case
            // there is no next vertex, pretend that the line is continuing straight,
            // meaning that we are just using the previous normal.
            glm::vec3 tempCoord = nextCoordinate - currentCoordinate;
            nextNormal = BucketUtils::isValid(nextCoordinate) ? BucketUtils::perp(
                    BucketUtils::unit(BucketUtils::convertPoint(tempCoord))) : prevNormal;

            // If we still don't have a previous normal, this is the beginning of a
            // non-closed line, so we're doing a straight "join".
            if (!BucketUtils::isValid(prevNormal)) {
                prevNormal.x = nextNormal.x;
                prevNormal.y = nextNormal.y;
                prevNormal.z = nextNormal.z;
            }

            // Determine the normal of the join extrusion. It is the angle bisector
            // of the segments between the previous line and the next line.
            // In the case of 180° angles, the prev and next normals cancel each other out:
            // prevNormal + nextNormal = (0, 0), its magnitude is 0, so the unit vector would be
            // undefined. In that case, we're keeping the joinNormal at (0, 0), so that the cosHalfAngle
            // below will also become 0 and miterLength will become Infinity.

            glm::vec3 joinNormal(prevNormal.x + nextNormal.x, 0,
                                 prevNormal.z + nextNormal.z);
            if (joinNormal.x != 0 || joinNormal.z != 0) {
                joinNormal = BucketUtils::unit(joinNormal);
            }

            /*  joinNormal     prevNormal
             *             ↖      ↑
             *                .________. prevVertex
             *                |
             * nextNormal  ←  |  currentVertex
             *                |
             *     nextVertex !
             *
             */
            // Calculate the length of the miter (the ratio of the miter to the width).
            // Find the cosine of the angle between the next and join normals
            // using dot product. The inverse of that is the miter length.
            const double cosHalfAngle =
                    joinNormal.x * nextNormal.x + joinNormal.z * nextNormal.z;
            //const double miterLength = cosHalfAngle != 0 ? 1 / cosHalfAngle : DOUBLE_INFINITY;
            const double miterLength = cosHalfAngle >= 0.01 ? 1 / cosHalfAngle : DOUBLE_INFINITY;

            const bool isSharpCorner = cosHalfAngle < COS_HALF_SHARP_CORNER &&
                    BucketUtils::isValid(prevCoordinate) &&
                    BucketUtils::isValid(nextCoordinate);

            if (isSharpCorner && i > first) {
                const double prevSegmentLength = BucketUtils::dist(currentCoordinate, prevCoordinate);
                if (prevSegmentLength > 2.0 / dHalfHeight * sharpCornerOffset) {
                    glm::vec3 newPrevVertex(currentCoordinate.x, currentCoordinate.y,
                                            currentCoordinate.z);
                    glm::vec3 tempCoord = currentCoordinate - prevCoordinate;
                    newPrevVertex = newPrevVertex - BucketUtils::convertPoint(
                            BucketUtils::convertPoint(tempCoord) *
                                    (float)(sharpCornerOffset / prevSegmentLength));
                    distance += BucketUtils::dist(newPrevVertex, prevCoordinate);
                    addCurrentVertex(newPrevVertex, distance, prevNormal, 0, 0, false, startVertex,
                                     triangleStore);
                    prevCoordinate.x = newPrevVertex.x;
                    prevCoordinate.y = newPrevVertex.y;
                    prevCoordinate.z = newPrevVertex.z;
                    //LOGI("isSharpCorner 0 [%f,%f,%f]",  (double)newPrevVertex.x(), (double)newPrevVertex.y(), (double)newPrevVertex.z());
                }
            }
            // The join if a middle vertex, otherwise the cap
            const bool middleVertex =
                    BucketUtils::isValid(prevCoordinate) && BucketUtils::isValid(nextCoordinate);
            int currentJoin = LineJoinTypeMiter;
            const int currentCap = BucketUtils::isValid(nextCoordinate) ? beginCap : endCap;

            if (middleVertex) {
                if (currentJoin == LineJoinTypeRound) {
                    if (miterLength < LineRoundLimit) {
                        currentJoin = LineJoinTypeMiter;
                    } else if (miterLength <= 2) {
                        currentJoin = LineJoinTypeFakeRound;
                    }
                }

                if (currentJoin == LineJoinTypeMiter && miterLength > miterLimit) {
                    currentJoin = LineJoinTypeBevel;
                }

                if (currentJoin == LineJoinTypeBevel) {
                    // The maximum extrude length is 128 / 63 = 2 times the width of the line
                    // so if miterLength >= 2 we need to draw a different type of bevel here.
                    if (miterLength > 2) {
                        currentJoin = LineJoinTypeFlipBevel;
                    }

                    // If the miterLength is really small and the line bevel wouldn't be visible,
                    // just draw a miter join to save a triangle.
                    if (miterLength < miterLimit) {
                        currentJoin = LineJoinTypeMiter;
                    }
                }
            }

            /*currentJoin = LineJoinTypeRound;

            //LOGI("addGeometry coor	[ %f,%f]", currentCoordinate.x(), currentCoordinate.z());
            if(miterLength > 100.0)
            {
                currentJoin = LineJoinTypeFlipBevel;
                LOGI("addGeometry jointype	%f, %d %f, %d,[ %f,%f] [ %f,%f]", miterLength, currentJoin, cosHalfAngle, middleVertex==true, currentCoordinate.x(), currentCoordinate.z(),
                    nextCoordinate.x(), nextCoordinate.z());
            }*/

            //LOGI("addGeometry jointype	%f, %d %f, %d,[ %f,%f] [ %f,%f]", miterLength, currentJoin, cosHalfAngle, middleVertex==true, currentCoordinate.x(), currentCoordinate.z(),
            //				nextCoordinate.x(), nextCoordinate.z());

            // Calculate how far along the line the currentVertex is
            if (BucketUtils::isValid(prevCoordinate))
                distance += BucketUtils::dist(currentCoordinate, prevCoordinate);

            if (middleVertex && currentJoin == LineJoinTypeMiter) {
                joinNormal = joinNormal * (float) miterLength;
                addCurrentVertex(currentCoordinate, distance, joinNormal, 0, 0, false, startVertex,
                                 triangleStore);

            } else if (middleVertex && currentJoin == LineJoinTypeFlipBevel) {
                // miter is too big, flip the direction to make a beveled join
                //LOGI("addGeometry currentCoordinate [%f,%f,%f]", currentCoordinate.x(), currentCoordinate.y(), currentCoordinate.z());
                //LOGI("addGeometry nextCoordinate [%f,%f,%f]", nextCoordinate.x(), nextCoordinate.y(), nextCoordinate.z());

                if (miterLength > 100) {
                    // Almost parallel lines
                    joinNormal = nextNormal * -1.0f;
                } else {
                    const double direction =
                            prevNormal.x * nextNormal.z - prevNormal.z * nextNormal.x > 0
                            ? -1 : 1;
                    const double bevelLength =
                            miterLength * BucketUtils::mag(prevNormal + nextNormal) /
                                    BucketUtils::mag(prevNormal - nextNormal);
                    joinNormal = BucketUtils::perp(joinNormal) * (float)(bevelLength * direction);
                }

                addCurrentVertex(currentCoordinate, distance, joinNormal, 0, 0, false, startVertex,
                                 triangleStore);

                addCurrentVertex(currentCoordinate, distance, joinNormal * -1.0f, 0, 0, false,
                                 startVertex, triangleStore);
            } else if (middleVertex &&
                       (currentJoin == LineJoinTypeBevel || currentJoin == LineJoinTypeFakeRound)) {
                const bool lineTurnsLeft =
                        (prevNormal.x * nextNormal.z - prevNormal.z * nextNormal.x) > 0;
                const double offset = -sqrt(miterLength * miterLength - 1) / dHalfHeight;
                float offsetA;
                float offsetB;

                if (lineTurnsLeft) {
                    offsetB = 0;
                    offsetA = offset;
                } else {
                    offsetA = 0;
                    offsetB = offset;
                }

                // Close previous segement with bevel
                if (!startOfLine) {
                    addCurrentVertex(currentCoordinate, distance, prevNormal, offsetA, offsetB,
                                     false, startVertex, triangleStore);
                }

                if (currentJoin == LineJoinTypeFakeRound) {
                    // The join angle is sharp enough that a round join would be visible.
                    // Bevel joins fill the gap between segments with a single pie slice triangle.
                    // Create a round join by adding multiple pie slices. The join isn't actually round, but
                    // it looks like it is at the sizes we render lines at.

                    // Add more triangles for sharper angles.
                    // This math is just a good enough approximation. It isn't "correct".
                    const int n = floor((0.5 - (cosHalfAngle - 0.5)) * 8);

                    for (int m = 0; m < n; m++) {
                        glm::vec3 approxFractionalJoinNormal = BucketUtils::unit(
                                nextNormal * (float)((m + 1.0) / (n + 1.0)) + prevNormal);
                        addPieSliceVertex(currentCoordinate, distance, approxFractionalJoinNormal,
                                          lineTurnsLeft, startVertex, triangleStore);
                    }

                    addPieSliceVertex(currentCoordinate, distance, joinNormal, lineTurnsLeft,
                                      startVertex, triangleStore);

                    for (int k = n - 1; k >= 0; k--) {
                        glm::vec3 approxFractionalJoinNormal = BucketUtils::unit(
                                prevNormal * (float)((k + 1.0) / (n + 1.0)) + nextNormal);
                        addPieSliceVertex(currentCoordinate, distance, approxFractionalJoinNormal,
                                          lineTurnsLeft, startVertex, triangleStore);
                    }
                }

                // Start next segment
                if (BucketUtils::isValid(nextCoordinate)) {
                    addCurrentVertex(currentCoordinate, distance, nextNormal, -offsetA, -offsetB,
                                     false, startVertex, triangleStore);
                }


            } else if (!middleVertex && currentCap == LineCapTypeButt) {
                if (!startOfLine) {
                    // Close previous segment with a butt
                    addCurrentVertex(currentCoordinate, distance, prevNormal, 0, 0, false,
                                     startVertex, triangleStore);
                }

                // Start next segment with a butt
                if (BucketUtils::isValid(nextCoordinate)) {
                    addCurrentVertex(currentCoordinate, distance, nextNormal, 0, 0, false,
                                     startVertex, triangleStore);
                }


            } else if (!middleVertex && currentCap == LineCapTypeSquare) {
                if (!startOfLine) {
                    // Close previous segment with a square cap
                    addCurrentVertex(currentCoordinate, distance, prevNormal, 1, 1, false,
                                     startVertex, triangleStore);

                    // The segment is done. Unset vertices to disconnect segments.
                    e1 = e2 = -1;
                }

                // Start next segment
                if (BucketUtils::isValid(nextCoordinate)) {
                    addCurrentVertex(currentCoordinate, distance, nextNormal, -1, -1, false,
                                     startVertex, triangleStore);
                }


            } else if (middleVertex ? currentJoin == LineJoinTypeRound : currentCap ==
                                                                         LineCapTypeRound) {
                if (!startOfLine) {
                    // Close previous segment with a butt
                    addCurrentVertex(currentCoordinate, distance, prevNormal, 0, 0, false,
                                     startVertex, triangleStore);

                    // Add round cap or linejoin at end of segment
                    addCurrentVertex(currentCoordinate, distance, prevNormal, 1.0, 1.0, true,
                                     startVertex, triangleStore);

                    // The segment is done. Unset vertices to disconnect segments.
                    e1 = e2 = -1;
                }

                // Start next segment with a butt
                if (BucketUtils::isValid(nextCoordinate)) {
                    // Add round cap before first segment
                    addCurrentVertex(currentCoordinate, distance, nextNormal, -1.0, -1.0, true,
                                     startVertex, triangleStore);

                    addCurrentVertex(currentCoordinate, distance, nextNormal, 0, 0, false,
                                     startVertex, triangleStore);
                }
            }

            if (isSharpCorner && i < len - 1) {
                const double nextSegmentLength = BucketUtils::dist(currentCoordinate, nextCoordinate);
                if (nextSegmentLength > 2 * sharpCornerOffset) {
                    glm::vec3 newCurrentVertex(currentCoordinate.x, currentCoordinate.y,
                                               currentCoordinate.z);
                    glm::vec3 tempVec = BucketUtils::convertPoint(nextCoordinate - currentCoordinate) *
                            (float)(sharpCornerOffset / nextSegmentLength);
                    newCurrentVertex = newCurrentVertex + BucketUtils::convertPoint(tempVec);
                    distance += BucketUtils::dist(newCurrentVertex, currentCoordinate);
                    addCurrentVertex(newCurrentVertex, distance, nextNormal, 0, 0, false,
                                     startVertex, triangleStore);
                    currentCoordinate = newCurrentVertex;

                    //LOGI("isSharpCorner [%f,%f,%f]",  (double)newCurrentVertex.x(), (double)newCurrentVertex.y(), (double)newCurrentVertex.z());
                }
            }

            startOfLine = false;
        }

        /*const std::size_t endVertex = vertices.vertexSize();
        const std::size_t vertexCount = endVertex - startVertex;

        if (segments.empty() || segments.back().vertexLength + vertexCount > UINT16_INFINITY)
        {
            segments.emplace_back(startVertex, triangles.indexSize());
        }

        auto& segment = segments.back();
        assert(segment.vertexLength <= std::numeric_limits<uint16_t>::max());
        uint16_t index = segment.vertexLength;

        for (const auto& triangle : triangleStore)
        {
            triangles.emplace_back(index + triangle.a, index + triangle.b, index + triangle.c);
        }

        segment.vertexLength += vertexCount;
        segment.indexLength += triangleStore.size() * 3;*/
        for (int i = 0; i < triangleStore.size(); i++) {
            TriangleElement triangle = triangleStore[i];
            //LOGI("INDEX buffer %d,%d,%d", triangle.a, triangle.b, triangle.c);
            mTriangles.push_back(triangle.a);
            mTriangles.push_back(triangle.b);
            mTriangles.push_back(triangle.c);
        }


    }

    void LineBucket::addCurrentVertex(glm::vec3 currentCoordinate,
                                      double &distance,
                                      glm::vec3 normal,
                                      double endLeft,
                                      double endRight,
                                      bool round,
                                      int startVertex,
                                      std::vector<TriangleElement> &triangleStore) {
        glm::vec3 extrude(normal.x, normal.y, normal.z);
        //LOGI("addCurrentVertex coor [%f, %f,%f] normal [%f, %f,%f] %f,%f,%d", (double)currentCoordinate.x(), (double)currentCoordinate.y(), (double)currentCoordinate.z(),
        //		(double)normal.x(), (double)normal.y(), (double)normal.z(), endLeft, endRight, round==true);
        if (endLeft) {
            extrude = extrude - BucketUtils::perp(normal) * (float)endLeft;
        }

        vertices.add(currentCoordinate, extrude * (float) extrudeScale, round, false, endLeft,
                     distance * LINE_DISTANCE_SCALE);
        e3 = vertices.size() - 1 - startVertex;
        if (e1 >= 0 && e2 >= 0) {
            triangleStore.push_back(TriangleElement(e1, e2, e3));
        }
        e1 = e2;
        e2 = e3;

        extrude = normal * -1.0f;
        if (endRight) {
            extrude = extrude - BucketUtils::perp(normal) * (float)endRight;
        }
        vertices.add(currentCoordinate, extrude * (float) extrudeScale, round, true, -endRight,
                     distance * LINE_DISTANCE_SCALE);
        e3 = vertices.size() - 1 - startVertex;
        if (e1 >= 0 && e2 >= 0) {
            triangleStore.push_back(TriangleElement(e1, e2, e3));
        }
        e1 = e2;
        e2 = e3;

        // There is a maximum "distance along the line" that we can store in the buffers.
        // When we get close to the distance, reset it to zero and add the vertex again with
        // a distance of zero. The max distance is determined by the number of bits we allocate
        // to `linesofar`.
        if (distance > MAX_LINE_DISTANCE / 2.0f) {
            distance = 0;
            addCurrentVertex(currentCoordinate, distance, normal, endLeft, endRight, round,
                             startVertex, triangleStore);
        }
    }

    void LineBucket::addPieSliceVertex(glm::vec3 currentVertex,
                                       double distance,
                                       glm::vec3 extrude,
                                       bool lineTurnsLeft,
                                       std::size_t startVertex,
                                       std::vector<TriangleElement> &triangleStore) {
        glm::vec3 flippedExtrude(extrude.x, extrude.y, extrude.z);


        flippedExtrude = flippedExtrude * (lineTurnsLeft ? -1.0f : 1.0f);
        vertices.add(currentVertex, flippedExtrude * (float) extrudeScale, false, lineTurnsLeft, 0,
                     distance * LINE_DISTANCE_SCALE);
        e3 = vertices.size() - 1 - startVertex;
        if (e1 >= 0 && e2 >= 0) {
            triangleStore.push_back(TriangleElement(e1, e2, e3));
        }

        if (lineTurnsLeft) {
            e2 = e3;
        } else {
            e1 = e3;
        }
    }


    std::vector<glm::vec3> &LineBucket::getPos() {
        return vertices.getPos();
    }

    std::vector<glm::vec4> &LineBucket::getData() {
        return vertices.getData();
    }

    std::vector<glm::vec3> &LineBucket::getNormal() {
        return vertices.getNormal();
    }

    std::vector<glm::vec2> &LineBucket::getDir() {
        return vertices.getDir();
    }

    std::vector<int> &LineBucket::getIndexBuffer() {
        return mTriangles;
    }

}


