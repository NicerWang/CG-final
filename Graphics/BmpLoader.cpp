#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "BmpLoader.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(suppress : 4996)


void BmpLoader::load(const char* filename) {
    FILE* file = 0;
    fopen_s(&file, filename, "rb");
    if (!file) 
    {
        std::cout << "[Missing Textures]\n";
        exit(-1);
    }
    fread(&bfh, sizeof(BITMAPFILEHEADER), 1, file);
    if (bfh.bfType != 0x4D42)
    {
        std::cout << "[CRASH] Only support .bmp texture\n";
        exit(-1);
    }
    fread(&bih, sizeof(BITMAPINFOHEADER), 1, file);
    if (bih.biSizeImage == 0)
        bih.biSizeImage = bih.biHeight * bih.biWidth * 3;
    textureData = new unsigned char[bih.biSizeImage];
    fseek(file, bfh.bfOffBits, SEEK_SET);
    fread(textureData, 1, bih.biSizeImage, file);
    unsigned char temp;
    for (int i = 0; i < bih.biSizeImage; i += 3)
    {
        temp = textureData[i];
        textureData[i] = textureData[i + 2];
        textureData[i + 2] = temp;
    }
    iWidth = bih.biWidth;
    iHeight = bih.biHeight;
    fclose(file);
}

BmpLoader::~BmpLoader()
{
    delete[] textureData;
}