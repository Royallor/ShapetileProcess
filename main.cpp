#include <iostream>
#include <fstream>
#include <shapefil.h>
#if (defined(__WIN32)) ||(defined(__WIN64))
#include <conic.h>
#endif

using namespace std;
void systemEndian(){
    uint i=0x01020304;
    printf("%p\n",&i);
    auto * p= (unsigned char*)&i;
    if(p[0]==0x04){
        printf("little endian");
    }
    else{
        printf("big endian");
    }
}
int main(int argc,char** argv) {
    systemEndian();
    int g_count,gShapeType,gWidth,gDecimals;
    double adfMinBound[4],adfMaxBound[4];
    char *inputFile= nullptr;
    inputFile=argv[1];
    auto fileHandle=SHPOpen(inputFile,"rb");
    if(fileHandle== nullptr){
        printf("Unable to open:%s\n",argv[1]);
        exit(1);
    }
    SHPGetInfo(fileHandle,&g_count,&gShapeType,adfMinBound,adfMaxBound);
    for(int i=0;i<g_count;i++){
        auto pShape= SHPReadObject(fileHandle,i);
        if(pShape== nullptr){
            cout<<"read object error."<<endl;
        }
    }
}
