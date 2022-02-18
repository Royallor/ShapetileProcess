//
// Created by Chikee on 2022/2/14.
//

#ifndef SHAPEREADER_H
#define SHAPEREADER_H

#include <shapefil.h>
#include <iostream>

class ShapeReader
{
private:
    SHPHandle m_shp;
    DBFHandle m_dbf;
    SHPObject m_obj;
    int m_count = -1;
    int m_shapeType = -1;
    double m_minBound[4];
    double m_maxBound[4];
    int numberOfFeatures = 0;

public:
    ShapeReader(std::string fileName);

    ~ShapeReader();

    void getInfo();

    void (*worker)(char *f);
};

#endif // SHAPETILEPROCESS_SHAPE_H
