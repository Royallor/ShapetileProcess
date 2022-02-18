#include <iostream>
#include <shapefil.h>
#include <iconv.h>
#include <string>
#include <cstring>
#include "CoreStruct.hpp"

#if (defined(__WIN32)) || (defined(__WIN64))
#include <conic.h>
#endif
using namespace std;

void test() {
    const char *str = "测试";
    string a = str;
    wstring wstr;
    cout << str << endl;
    auto fp = fopen("./a.txt", "w");
    fwrite(a.c_str(), a.size(), 1024, fp);

}

int GbkToUtf8(char *str_str, size_t src_len, char *dst_str, size_t dst_len) {
    iconv_t cd;
    char **pin = &str_str;
    char **pout = &dst_str;

    cd = iconv_open("utf8", "gbk");
    if (cd == 0)
        return -1;
    memset(dst_str, 0, dst_len);
    if (iconv(cd, pin, &src_len, pout, &dst_len) == -1)
        return -1;
    iconv_close(cd);
    **pout = '\0';

    return 0;
}

int Utf8ToGbk(char *src_str, size_t src_len, char *dst_str, size_t dst_len) {
    iconv_t cd;
    char **pin = &src_str;
    char **pout = &dst_str;

    cd = iconv_open("gbk", "utf8");
    if (cd == nullptr)
        return -1;
    memset(dst_str, '\0', dst_len);
    if (iconv(cd, pin, &src_len, pout, &dst_len) == -1)
        return -1;
    iconv_close(cd);
    **pout = '\0';

    return 0;
}

int main(int argc, char **argv) {
    int shapeCount, shapeType;
    double minBound[4], maxBound[4];
    auto shpHandle = SHPOpen("../data/Buildingarea.shp", "rb");
    auto dbfHandle = DBFOpen("../data/Buildingarea.dbf", "rb");
    char dst_utf8[1024] = {0};
    auto fp = fopen("./res.txt", "w");
    auto fp_gbk = fopen("./res_gbk.txt", "w");
    SHPGetInfo(shpHandle, &shapeCount, &shapeType, minBound, maxBound);
    for (int i = 0; i < shapeCount; i++) {
//        auto pShape= SHPReadObject(shpHandle,i);
        char szTitle[12];
        int nWidth;
        int nDecimals;
        for (int j = 0; j < DBFGetFieldCount(dbfHandle); j++) {
            auto eType = DBFGetFieldInfo(dbfHandle, j, szTitle, &nWidth, &nDecimals);

            bool hit = true;
            char namec[12] = "NAMEC";
            for (int s = 0; s < 5; s++) {
                if (szTitle[s] != namec[s]) {
                    hit = false;
                    break;
                }
            }
            if (!hit) {
                continue;
            }
            string value;
            char *namecValue = nullptr;
            if (eType == FTString) {
                auto p = DBFReadStringAttribute(dbfHandle, i, j);
//                string msg (p);
//                memcpy(namecValue,msg.c_str(),msg.length()+1);
                namecValue = const_cast<char *>(p);
                value = DBFReadStringAttribute(dbfHandle, i, j);
            } else if (eType == FTInteger) {
                value = std::to_string(DBFReadIntegerAttribute(dbfHandle, i, j));
            } else if (eType == FTDouble) {
                value = std::to_string(DBFReadDoubleAttribute(dbfHandle, i, j));
            }


            // unix default is utf8
//            fprintf(fp, namecValue);
            stringstream ss=namecValue;
            char dst_gbk[sizeof(namecValue)];
            Utf8ToGbk(namecValue, strlen(namecValue), dst_gbk, sizeof(dst_gbk));
            fprintf(fp_gbk, dst_gbk);
//
//            GbkToUtf8(dst_gbk, strlen(dst_gbk), dst_utf8, sizeof(dst_utf8));
//            cout << "gbk to utf8: " << dst_utf8 << endl;
        }
    }
    fclose(fp);
    fclose(fp_gbk);
//    test();
}
