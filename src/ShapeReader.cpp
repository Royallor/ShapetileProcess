//
// Created by Chikee on 2022/2/14.
//
#include "ShapeReader.h"
#include "CoreStruct.hpp"
_NAMESPACE_BEGIN
ShapeReader::ShapeReader(std::string fileName) {
    m_shp= SHPOpen(fileName.c_str(),"rb");
    size_t i = fileName.find(".shp");
    m_dbf = DBFOpen(fileName.replace(i, 4, ".dbf").c_str(), "rb");
}
ShapeReader::~ShapeReader() {
    SHPClose(m_shp);
    DBFClose(m_dbf);
}
bool ShapeReader::readVectorInfoFromFile(const char *file, GlobalVectorInfo* pData) {
    auto handle=SHPOpen(file,"rb");
    if(handle== nullptr){
        printf("Unable to open:%s\n",file);
        exit(1);
    }
    int p_count,p_shapeType;
    double p_adfMinBound[4],p_adfMaxBound[4];
    SHPGetInfo(handle,&p_count,&p_shapeType,p_adfMaxBound,p_adfMinBound);
}
_NAMESPACE_END