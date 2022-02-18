//
// Created by Chikee on 2022/2/15.
//
#ifndef FEATURE_H
#define FEATURE_H
#include "Vector3.h"
#include "Go"
class Feature
{
private:
    std::uniptr<Geometry> m_geometry;
    std::map<std::string, std::string> m_attributes;

public:
    Feature(/* args */);
    ~Feature();
};

Feature::Feature(/* args */)
{
}

Feature::~Feature()
{
}

#endif