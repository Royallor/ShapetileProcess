#pragma once

#include "GeomUtil.hpp"
#include "base.hpp"

#include "AABB.hpp"
#include "Vector2.h"
#include "Vector3.h"
#include <iomanip>
#include <math.h>
#include <memory>
#include <set>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>
#include <map>

_NAMESPACE_BEGIN

// 球面
struct GeoCoord2 {
    double lat;  // 纬度[-90,90] 　
    double lon;  // 经度[-180,180]

    GeoCoord2() {}
    GeoCoord2(double _lat, double _lon)
        : lat(_lat)
        , lon(_lon) {
        if (!isValid()) {
            MT_WARN("lat(%.6f), lon(%.6f) is invalid", lat, lon)
        }
    }

    bool isValid() {
        if (lat > 90.0 || lat < -90.0 || lon > 180.0 || lon < -180.0)
            return false;
        return true;
    }

    bool operator==(const GeoCoord2& right) {
        return abs(lat - right.lat) < 1e-8 && abs(lon - right.lon) < 1e-8;
    }

    bool operator!=(const GeoCoord2& right) {
        return !(*this == right);
    }
};

struct TileId {
    std::uint32_t x;
    std::uint32_t y;
    std::uint16_t level;

    TileId() {}
    TileId(std::uint32_t a, std::uint32_t b, uint16_t c)
        : x(a)
        , y(b)
        , level(c) {}

    std::string toString() const {
        char temBuf[64];
        sprintf(temBuf, "%d_%d_%d", x, y, level);
        return std::string(temBuf);  //内存？
    }

    static bool fromString(const std::string& str, TileId* outId) {
        VALID_PTR_BOOL(outId)
        uint32_t level, x, y;
        sscanf(str.data(), "%d_%d_%d", &x, &y, &level);
        outId->x = x;
        outId->level = level;
        outId->y = y;
        return true;
    }

    bool operator==(const TileId& right) const {
        if (x == right.x && y == right.y && level == right.level)
            return true;
        else
            return false;
    }

    bool operator!=(const TileId& right) const {
        if (x != right.x || y != right.y || level != right.level)
            return true;
        else
            return false;
    }

    friend std::ostream& operator<<(std::ostream& output, const TileId& id) {
        output << "[" << id.x << ", " << id.y << ", " << id.level << "]";
        return output;
    }
};

struct Node {
    std::string id;
    GeoCoord2 pos;
    double height;
    std::unordered_map<std::string, std::string> tags;
};

struct Way {
    bool isValid() const {
        return nodeIds.size() > 1;
    }

    std::string id;
    std::vector<std::pair<std::string, std::string>> constrains;  // only be used for roadsurface
    std::vector<std::string> nodeIds;
    std::unordered_map<std::string, std::string> tags;
};

struct Relation {
    std::string id;
    std::unordered_map<std::string, std::string> tags;
    std::unordered_map<std::string, vector<std::pair<std::string, std::string>>> members;
};

struct GlobalVectorInfo {
    std::unordered_map<std::string, Node*> wayNodes;
    std::unordered_map<std::string, Node*> objNodes;
    std::unordered_map<std::string, Way*> originWays;

    std::unordered_map<std::string, Way*> roadSurfaceWays;
    std::unordered_map<std::string, Relation*> floorsRelations;
    std::unordered_map<std::string, Relation*> laneGroupRelations;
    std::unordered_map<std::string, Relation*> junctionRelations;
    std::unordered_map<std::string, Relation*> objectImpactRelations;

    std::unordered_map<std::string, Node*> splitNodes;
    std::unordered_map<std::string, Way*> splitWays;

    int64_t maxNodeId;
    int64_t maxWayId;
    AABB aabbLLA;
    AABB aabbProjection;
    GlobalVectorInfo() {
        maxNodeId = maxWayId = INT64_MIN;
    }

    ~GlobalVectorInfo() {
        for (auto nodeIter = objNodes.begin(); nodeIter != objNodes.end(); nodeIter++)
            delete nodeIter->second;

        for (auto nodeIter = splitNodes.begin(); nodeIter != splitNodes.end(); nodeIter++)
            delete nodeIter->second;

        for (auto nodeIter = wayNodes.begin(); nodeIter != wayNodes.end(); nodeIter++)
            delete nodeIter->second;

        for (auto wayIter = originWays.begin(); wayIter != originWays.end(); wayIter++)
            delete wayIter->second;

        for (auto wayIter = splitWays.begin(); wayIter != splitWays.end(); wayIter++)
            delete wayIter->second;

        for (auto wayIter = roadSurfaceWays.begin(); wayIter != roadSurfaceWays.end(); wayIter++)
            delete wayIter->second;

        for (auto relationIter = floorsRelations.begin(); relationIter != floorsRelations.end(); relationIter++)
            delete relationIter->second;

        for (auto relationIter = laneGroupRelations.begin(); relationIter != laneGroupRelations.end(); relationIter++)
            delete relationIter->second;

        for (auto relationIter = junctionRelations.begin(); relationIter != junctionRelations.end(); relationIter++)
            delete relationIter->second;

        for (auto relationIter = objectImpactRelations.begin(); relationIter != objectImpactRelations.end();
             relationIter++)
            delete relationIter->second;

        objNodes.clear();
        splitNodes.clear();
        wayNodes.clear();
        originWays.clear();
        splitWays.clear();

        roadSurfaceWays.clear();
        floorsRelations.clear();
        laneGroupRelations.clear();
        junctionRelations.clear();
        objectImpactRelations.clear();
    }
};

struct OsmTileInfo {
    TileId tileId;
    AABB llaAABB;
    Vector3<double> projectionAnchorPoint;
};

struct OsmTile {
    OsmTileInfo tileInfo;
    std::vector<std::string> originWayIds;
    std::vector<std::string> splitWayIds;
    std::vector<std::string> objNodeIds;
    GlobalVectorInfo* pData;

    OsmTile()
        : pData(nullptr) {}
    OsmTile(GlobalVectorInfo* data)
        : pData(data) {}
    ~OsmTile() {
        originWayIds.clear();
        splitWayIds.clear();
        objNodeIds.clear();
        pData = nullptr;
    }
};

// refact this please
struct Primitives {
    std::string type;
    std::vector<Vector3<float>> points;
    std::vector<Vector3<float>> normals;
    std::vector<ushort> batchIds;
};

struct PrimitiveNormalLines {
    std::string type;
    std::vector<Vector3<float>> points;
    std::vector<Vector3<float>> colors;
};
struct PrimitiveQuads : public Primitives {
    std::vector<Vector2<float>> texcoords;
    std::vector<uint32_t> indices;
};

struct PrimitiveCircles : public Primitives {
    std::vector<Vector2<float>> texcoords;
    std::vector<uint32_t> indices;
};

struct PrimitivePolygons : public Primitives {
    std::vector<Vector3<float>> colors;
    std::vector<Vector2<float>> texcoords;
    std::vector<uint32_t> indices;
};

struct PrimitiveLineStrips : public Primitives {
    std::vector<uint32_t> indices;
};

struct PrimitiveLines : public Primitives {
    std::vector<uint32_t> indices;
};

struct Curbs : public Primitives {
    const std::string faceName[6] = {"TopRoadCurbFace",   "BottomRoadCurbFace", "LeftRoadCurbFace",
                                     "RightRoadCurbFace", "FrontRoadCurbFace",  "BackRoadCurbFace"};
    std::vector<uint32_t> indices[6];
};

struct PrimitiveStaticCubes : public Primitives {
    std::vector<Vector3<float>> colors;
    std::vector<uint32_t> indices;
};

struct BasicObject {
    BasicObject() {
        type = "default";
    }
    virtual ~BasicObject() {}
    std::string id;
    std::string name;
    std::string type;
    std::string textureType;
    std::vector<Vector3<double>> points;
};

// 根据direction来进行划分
struct RoadMark : public BasicObject {
    Vector3<double> anchor;
    bool isOrdered;
};

// 两种
// 1.obj_type == board
// 2.obj_type == traffic-sign && shape == rectangle
struct TrafficBoard : public BasicObject {
    Vector3<double> anchor;
};

// single-spot / horizonta-3spot
struct TrafficLight : public BasicObject {
    std::string alignment;
    Vector3<double> anchor;
};

// NOTICE:需要兼容tag中的geom和keypoints
struct Pole : public BasicObject {
    Vector3<double> anchor;
};

struct Poi : public BasicObject {
    Vector3<double> anchor;
};

// 车道线
// 解析way内的highway的标签
struct Lane : public BasicObject {
    std::vector<std::pair<std::size_t, std::size_t>> constrains;
};

_NAMESPACE_END
