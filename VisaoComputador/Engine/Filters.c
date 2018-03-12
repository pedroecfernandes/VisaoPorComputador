//
//  Filters.c
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 26/02/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS 


#ifdef OSX
#include "Filters.h"
#include "Engine.h"
#include <stdbool.h>
#else
// TODO: Márcio
#endif

bool ApplyInvertRGB(Image *image)
{
    unsigned char *data = (unsigned char *)image->data;
    int width = image->width;
    int height = image->height;
    int bytesperline = image->width*image->channels;
    int channels = image->channels;
    int x, y;
    long int pos;
    
    if ((width <= 0) || (height <= 0) || (image->data == NULL)) return false;
    
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

bool ApplyInvertGrayScale(Image *image)
{
    int i;
    
    for (i=0; i<image->bytesperline*image->height; i+=image->channels) {
        image->data[i] = 255 - image->data[i];
    }
    
    return true;
}
