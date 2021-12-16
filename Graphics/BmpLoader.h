#pragma once
#include <windows.h>

class BmpLoader {
public:
    unsigned char* textureData;
    int iWidth, iHeight;
    ~BmpLoader();
    void load(const char*);
private:
    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;
};
