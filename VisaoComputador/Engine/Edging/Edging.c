//
//  Outliners.c
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 30/04/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//

#include <stdio.h>
#include "Edging.h"

bool ApplyPrewittEdging(Image *src, Image *dst, float th)
{
    unsigned char *data = (unsigned char *)src->data;
    int width = src->width;
    int height = src->height;
    int byteperline = src->width*src->channels;
    int channels = src->channels;
    int x, y;
    long int pos;
    long int posA, posB, posC, posD, posE, posF, posG, posH;
    long int mag, mx, my;
    
    if ((width <= 0) || (height <= 0) || (src->data == NULL)) return 0;
    if (channels != 1) return 0;
    
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width;x++)
        {
            pos = y * byteperline + x * channels;
            
            posA = (y - 1)* byteperline + (x - 1) * channels;
            posB = (y - 1)* byteperline + (x)* channels;
            posC = (y - 1)* byteperline + (x + 1)* channels;
            posD = (y)* byteperline + (x - 1)* channels;
            posE = (y)* byteperline + (x + 1)* channels;
            posF = (y + 1)* byteperline + (x - 1)* channels;
            posG = (y + 1)* byteperline + (x)* channels;
            posH = (y + 1)* byteperline + (x + 1)* channels;
            mx = ((-1 * data[posA]) + (1 * data[posC]) + (-1 * data[posD]) + (1 * data[posE]) + (-1 * data[posF]) + (1 * data[posH])) / 3;
            my = ((-1 * data[posA]) + (1 * data[posF]) + (-1 * data[posB]) + (1 * data[posG]) + (-1 * data[posC]) + (1 * data[posH])) / 3;
            
            mag = sqrt((mx*mx) + (my * my));
            
            if (mag > th)
                dst->data[pos] = 255;
            else
                dst->data[pos] = 0;
        }
    }
    return 1;
}

bool ApplySobelEdging(Image *src, Image *dst, float th)
{
    unsigned char *data = (unsigned char *)src->data;
    int width = src->width;
    int height = src->height;
    int byteperline = src->width*src->channels;
    int channels = src->channels;
    int x, y;
    long int pos;
    long int posA, posB, posC, posD, posE, posF, posG, posH;
    long int mag, mx, my;
    
    if ((width <= 0) || (height <= 0) || (src->data == NULL)) return 0;
    if (channels != 1) return 0;
    
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width;x++)
        {
            pos = y * byteperline + x * channels;
            
            posA = (y - 1)* byteperline + (x - 1) * channels;
            posB = (y - 1)* byteperline + (x)* channels;
            posC = (y - 1)* byteperline + (x + 1)* channels;
            posD = (y)* byteperline + (x - 1)* channels;
            posE = (y)* byteperline + (x + 1)* channels;
            posF = (y + 1)* byteperline + (x - 1)* channels;
            posG = (y + 1)* byteperline + (x)* channels;
            posH = (y + 1)* byteperline + (x + 1)* channels;
            
            mx = ((-1 * data[posA]) + (1 * data[posC]) + (-2 * data[posD]) + (2 * data[posE]) + (-1 * data[posF]) + (1 * data[posH])) / 3;
            my = ((-1 * data[posA]) + (1 * data[posF]) + (-2 * data[posB]) + (2 * data[posG]) + (-1 * data[posC]) + (1 * data[posH])) / 3;
            
            mag = sqrt((mx*mx) + (my * my));
            
            if (mag > th)
                dst->data[pos] = 255;
            else
                dst->data[pos] = 0;
        }
    }
    return 1;
}
