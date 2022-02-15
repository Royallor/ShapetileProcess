#include <iostream>
#include <shapefil.h>

#if (defined(__WIN32)) ||(defined(__WIN64))
#include <conic.h>
#endif

using namespace std;

int main(int argc,char** argv) {
    int g_count,g_pnShapeType,gWidth,gDecimals;
    double adfMinBound[4],adfMaxBound[4];
    char *inputFile= nullptr;
    inputFile=argv[1];
//    Shape shape;
    auto fileHandle=SHPOpen(inputFile,"rb");
    if(fileHandle== nullptr){
        printf("Unable to open:%s\n",argv[1]);
        exit(1);
    }
    SHPGetInfo(fileHandle,&g_count,&g_pnShapeType,adfMinBound,adfMaxBound);
    for(int i=0;i<g_count;i++) {
        auto pShape = SHPReadObject(fileHandle, i);
        if (pShape == nullptr) {
            cout << "read object error." << endl;
            break;
        }
    }
}
