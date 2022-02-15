//
// Created by Chikee on 2022/2/14.
//

#ifndef SHAPETILEPROCESS_SHAPE_H
#define SHAPETILEPROCESS_SHAPE_H
#include<shapefil.h>
#include "CoreStruct.hpp"
_NAMESPACE_BEGIN
class ShapeReader{
private:
    SHPHandle m_shp;
    DBFHandle m_dbf;
public:
    ShapeReader(std::string fileName);
    ~ShapeReader();
    bool readVectorInfoFromFile(const char* file,GlobalVectorInfo* pData);
};
_NAMESPACE_END
#endif //SHAPETILEPROCESS_SHAPE_H
