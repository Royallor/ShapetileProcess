#pragma once
#include "base.hpp"
#include "Vector2.h"
#include "Vector3.h"

_NAMESPACE_BEGIN

struct Node;
struct GeoCoord2;
struct Way;
struct GlobalVectorInfo;

class Coord2 {
  public:
    double x;
    double y;

    Coord2() {}
    Coord2(double _x, double _y)
        : x(_x)
        , y(_y) {}
    void set(double _x, double _y) {
        x = _x;
        y = _y;
    }
    bool operator==(const Coord2& right) const {
        if (doubleEqual(x, right.x) && doubleEqual(y, right.y))
            return true;
        else
            return false;
    }
    bool operator!=(const Coord2& right) const {
        if (!doubleEqual(x, right.x) || !doubleEqual(y, right.y))
            return true;
        else
            return false;
    }

    Coord2& operator=(const Coord2& right) {
        x = right.x;
        y = right.y;
        return *this;
    }

    static double distance(const Coord2& p0, const Coord2& p1) {
        double s = p1.x - p0.x;
        double r = p1.y - p0.y;
        return sqrt(s * s + r * r);
    }

    static double crossProduct(const Coord2& p1, const Coord2& p2) {
        return p1.x * p2.y - p1.y * p2.x;
    }

    static Coord2 lerp(const Coord2& p1, const Coord2& p2, double t) {
        return Coord2(p1.x + (p2.x - p1.x) * t, p1.y + (p2.y - p1.y) * t);
    }

    static Coord2 subtractPoints(const Coord2& p1, const Coord2& p2) {
        return Coord2(p1.x - p2.x, p1.y - p2.y);
    }
};
// 平面右x上y坐标系统，min值为距离原点较近的坐标,max值为距离原点较远坐标
class Rect {
  public:
    Coord2 min;
    Coord2 max;
    Rect() {}
    Rect(const Coord2& _min, const Coord2& _max)
        : min(_min)
        , max(_max) {}
    void getIntersectPoints(const Coord2& p0, const Coord2& p1, std::vector<Coord2>& points);
};

// translate from mearth-base file geos.js
bool getSegmentCrossCoord(const Coord2& p0, const Coord2& p1, const Coord2& p2, const Coord2& p3, Coord2* out);

bool isTwoSegmentCrossed(const Vector2<double>& a1, const Vector2<double>& a2, const Vector2<double>& b1,
                         const Vector2<double>& b2);

double calcWayLength(const Way& way, const GlobalVectorInfo* globleInfo);

// difference elevation
double diffElevationByNode(const Node& left, const Node& right, const GeoCoord2& diff);

void _resamplePolylineByDistance(const std::vector<Vector3<float>>& coords, double distance,
                                 std::vector<Vector3<float>>& outCoords);
//                     1----------3
//   ----------    ->  -          -
//                     2----------4

bool convertSolidPolyline2TriangleMesh(const std::vector<Vector3<float>>& points, float lineWidth,
                                       std::vector<Vector3<float>>& outPoints, std::vector<Vector3<float>>& outNormals);

bool convertDashPolyline2TriangleMesh(const std::vector<Vector3<float>>& points, float lineWidth, float resampleLength,
                                      std::vector<Vector3<float>>& outPoints, std::vector<Vector3<float>>& outNormals);

bool convertSolidPolyline2TriangleMeshWithIndices(const std::vector<Vector3<float>>& points, float lineWidth,
                                                  std::vector<Vector3<float>>& outPoints,
                                                  std::vector<Vector3<float>>& outNormals,
                                                  std::vector<unsigned int>& outIndexs, size_t currPosSize);
bool convertDashPolyline2TriangleMeshWithIndices(const std::vector<Vector3<float>>& points, float lineWidth,
                                                 float resampleLength, std::vector<Vector3<float>>& outPoints,
                                                 std::vector<Vector3<float>>& outNormals,
                                                 std::vector<unsigned int>& outIndexs, size_t currPosSize);

Vector3<float> lightingCalculation(Vector3<float>& normal, Vector3<float>& lightColor, Vector3<float>& objectColor);

template <typename T>
std::vector<Vector3<T>> douglasPeuckerAlgo(const std::vector<Vector3<T>>& originalPoints, const double limitDistance) {
    if (originalPoints.size() < 2) {
        return {};
    }
    Vector3<T> startToEnd = originalPoints.back() - originalPoints.front();
    size_t maxIndex = 0;
    double maxDistance = 0;
    for (size_t i = 0; i < originalPoints.size(); i++) {
        Vector3<T> startToNow = originalPoints[i] - originalPoints.front();
        double projectLength = startToNow * startToEnd / startToEnd.length();
        Vector3<T> projectVector = startToEnd / startToEnd.length() * projectLength;
        double curDistance = (startToNow - projectVector).length();
        if (curDistance > maxDistance) {
            maxDistance = curDistance;
            maxIndex = i;
        }
    }
    if (maxDistance > limitDistance) {
        std::vector<Vector3<T>> seq1(originalPoints.begin(), originalPoints.begin() + maxIndex + 1);
        std::vector<Vector3<T>> seq2(originalPoints.begin() + maxIndex, originalPoints.end());
        std::vector<Vector3<T>> res1 = douglasPeuckerAlgo(seq1, limitDistance);
        std::vector<Vector3<T>> res2 = douglasPeuckerAlgo(seq2, limitDistance);
        res1.insert(res1.end(), res2.begin() + 1, res2.end());
        return res1;
    } else {
        return {originalPoints.front(), originalPoints.back()};
    }
}
_NAMESPACE_END
