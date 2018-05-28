//
//  Filters.c
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 26/02/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS 


#ifdef OSX
#include "Filters.hpp"
#include "Engine.hpp"
#include <stdbool.h>
#else
#include "Filters.hpp"
#include "Engine.hpp"
#include <stdbool.h>
#include <stddef.h>
#endif


bool ApplyInvertRGB(IplImage *image)
{
    unsigned char *data = (unsigned char *)image->imageData;
    int width = image->width;
    int height = image->height;
    int bytesperline = image->width*image->nChannels;
    int channels = image->nChannels;
    int x, y;
    long int pos;
    
    if ((width <= 0) || (height <= 0) || (image->imageData == NULL)) return false;
    
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            pos = y * bytesperline + x * channels;
            
            data[pos] = 255 - data[pos];
            data[pos + 1] = 255 - data[pos+1];
            data[pos + 2] = 255 - data[pos+2];
        }
    }
    
    return true;
}

bool ApplyInvertGrayScale(IplImage *image)
{
    int i;
    
    for (i=0; i<(image->width*image->nChannels)*image->height; i+=image->nChannels) {
        image->imageData[i] = 255 - image->imageData[i];
    }
    
    return true;
}

bool ApplyInvertBinary(IplImage *image)
{
    int i;
    
    for (i=0; i<(image->width*image->nChannels)*image->height; i+=image->nChannels) {
        if (image->imageData[i] == 1)
            image->imageData[i] = 0;
        else
            image->imageData[i] = 1;
    }
    
    return true;
}
