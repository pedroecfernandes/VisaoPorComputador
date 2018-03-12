//
//  Conversors.c
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 26/02/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS 

#ifdef OSX
#include "Conversors.h"
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "Utils.h"
#else
// TODO: Márcio
#endif


bool ConvertRGBToBGR(Image *image)
{
    unsigned char *data = (unsigned char *)image->data;
    int width = image->width;
    int height = image->height;
    int bytesperlineRGB = image->width*image->channels;
    int channels = image->channels;
    int x, y;
    float r = 0.0, g = 0.0, b = 0.0;
    float rTemp = 0.0;
    long int posRGB;
    
    if ((width <= 0) || (height <= 0) || (image->data == NULL))
        return false;
    if (channels != 3)
        return false;
    
    if (image == NULL)
    {
        printf("ERROR!");
        getchar();
        
        return false;
    }
    
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            posRGB = y * bytesperlineRGB + x * channels;
            
            r = (float)data[posRGB];
            g = (float)data[posRGB + 1];
            b = (float)data[posRGB + 2];
            
            rTemp = r;
            
            
            data[posRGB] = b;
            data[posRGB + 2] = rTemp;
        }
    }
    
    return true;
}


bool ConvertRGBToGrayScaleBasedOnChannel(Image *image, Image *output, bool RChannel, bool GChannel, bool BChannel)
{
    unsigned char *data = (unsigned char *)image->data;
    int width = image->width;
    int height = image->height;
    int bytesperlineRGB = image->width*image->channels;
    int bytesperlineGray = output->width*output->channels;
    int channels = image->channels;
    int x, y;
    float r = 0.0, g = 0.0, b = 0.0;
    long int posRGB;
    long int posGray;
    
    if ((width <= 0) || (height <= 0) || (image->data == NULL))
        return false;
    if (channels != 3)
        return false;
    
    if (image == NULL)
    {
        printf("ERROR!");
        getchar();
        
        return false;
    }
    
    if (RChannel == false && GChannel == false && BChannel == false)
    {
        printf("You must select a channel!");
        getchar();
        
        return false;
    }
    
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            posRGB = y * bytesperlineRGB + x * channels;
            posGray = y * bytesperlineGray + x *output->channels;
            
            r = (float)data[posRGB];
            g = (float)data[posRGB + 1];
            b = (float)data[posRGB + 2];
            
            
            
            if (RChannel)
                output->data[posGray] = r;
            else if (GChannel)
                output->data[posGray] = g;
            else
                output->data[posGray] = b;
        }
    }
    
    return true;
}

bool ConvertRBGToHSV(Image *image)
{
    unsigned char *data = (unsigned char *)image->data;
    int width = image->width;
    int height = image->height;
    int bytesperline = image->width*image->channels;
    int channels = image->channels;
    int x, y;
    long int pos;
    float max = 0, min = 255;
    float s = 0.0, h = 0.0;
    float r = 0.0, g = 0.0, b = 0.0;
    
    if ((width <= 0) || (height <= 0) || (image->data == NULL)) return false;
    if (channels != 3) return 0;
    
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            pos = y * bytesperline + x * channels;
            r = (float)data[pos];
            g = (float)data[pos + 1];
            b = (float)data[pos + 2];
            
            max = Max3(r, g, b);
            if (max != 0.0)
            {
                min = Min3(r, g, b);
                
                s = (max - min) / max;
                
                s = s * 255.0f;
                if (max == 0.0)
                    h = 0.0;
                else
                {
                    if ((max == r) && (g >= b)) h = 60.0f * (g - b) / (max - min);
                    else if ((max == g) && (b > g)) h = 360.0f + 60.0f * (g - b) / (max - min);
                    else if (max == g) h = 120.0f + 60.0f * (b - r) / (max - min);
                    else h = 240.0f + 60.0f * (r - g) / (max - min);
                    
                    h = (h / 360.0) * 255.0;
                }
            }
            else
            {
                s = 0.0;
                h = 0.0;
            }
            
            data[pos] = (unsigned char)h;
            data[pos + 1] = (unsigned char)s;
            data[pos + 2] = (unsigned char)max;
        }
    }
    
    return true;
}
