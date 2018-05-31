//
//  Conversors.c
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 26/02/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS 

#ifdef OSX
#include "Conversors.hpp"
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "Utils.hpp"
#else
#include "Conversors.hpp"
#include <stdio.h>  // for NULL
#include "../Utils.hpp"

#endif


bool ConvertRGBToBGR(IplImage *image)
{
    unsigned char *data = (unsigned char *)image->imageData;
    int width = image->width;
    int height = image->height;
    int bytesperlineRGB = image->width*image->nChannels;
    int channels = image->nChannels;
    int x, y;
    float r = 0.0, g = 0.0, b = 0.0;
    float rTemp = 0.0;
    long int posRGB;
    
    if ((width <= 0) || (height <= 0) || (image->imageData == NULL))
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


bool ConvertRGBToGrayScaleBasedOnChannel(IplImage *image, IplImage *output, bool RChannel, bool GChannel, bool BChannel)
{
    unsigned char *data = (unsigned char *)image->imageData;
    int width = image->width;
    int height = image->height;
    int bytesperlineRGB = image->width*image->nChannels;
    int bytesperlineGray = output->width*output->nChannels;
    int channels = image->nChannels;
    int x, y;
    float r = 0.0, g = 0.0, b = 0.0;
    long int posRGB;
    long int posGray;
    
    if ((width <= 0) || (height <= 0) || (image->imageData == NULL))
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
            posGray = y * bytesperlineGray + x *output->nChannels;
            
            r = (float)data[posRGB];
            g = (float)data[posRGB + 1];
            b = (float)data[posRGB + 2];
            
            
            
            if (RChannel)
                output->imageData[posGray] = r;
            else if (GChannel)
                output->imageData[posGray] = g;
            else
                output->imageData[posGray] = b;
        }
    }
    
    return true;
}

bool ConvertBGRToHSV(IplImage *image)
{
    unsigned char *data = (unsigned char *)image->imageData;
    int width = image->width;
    int height = image->height;
    int bytesperline = image->width*image->nChannels;
    int channels = image->nChannels;
    int x, y;
    long int pos;
    float max = 0, min = 255;
    float s = 0.0, h = 0.0;
    float r = 0.0, g = 0.0, b = 0.0;
    
    if ((width <= 0) || (height <= 0) || (image->imageData == NULL)) return false;
    if (channels != 3) return 0;
    
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            pos = y * bytesperline + x * channels;
            r = (float)data[pos] + 2;
            g = (float)data[pos + 1];
            b = (float)data[pos];
            
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

bool ConvertRBGToHSV(IplImage *image)
{
    unsigned char *data = (unsigned char *)image->imageData;
    int width = image->width;
    int height = image->height;
    int bytesperline = image->width*image->nChannels;
    int channels = image->nChannels;
    int x, y;
    long int pos;
    float max = 0, min = 255;
    float s = 0.0, h = 0.0;
    float r = 0.0, g = 0.0, b = 0.0;
    
    if ((width <= 0) || (height <= 0) || (image->imageData == NULL)) return false;
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

bool ConvertHSVToRGB(IplImage *image)
{
    unsigned char *data = (unsigned char *)image->imageData;
    int width = image->width;
    int height = image->height;
    int bytesperline = image->width*image->nChannels;
    int channels = image->nChannels;
    int x, y;
    long int pos;
    float max = 0, min = 255;
    unsigned char s = 0.0, h = 0.0, v = 0.0;
    float r = 0.0, g = 0.0, b = 0.0;
    unsigned char region, remainder, p, q, t;
    
    if ((width <= 0) || (height <= 0) || (image->imageData == NULL)) return false;
    if (channels != 3) return 0;
    
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            pos = y * bytesperline + x * channels;
            h = (float)data[pos];
            s = (float)data[pos + 1];
            v = (float)data[pos + 2];
            
            if (s == 0)
            {
                r = v;
                g = v;
                b = v;
            }
            else
            {
                region = h / 43;
                remainder = (h - (region * 43)) * 6;
                
                p = (v * (255 - s)) >> 8;
                q = (v * (255 - ((s * remainder) >> 8))) >> 8;
                t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;
                
                switch (region)
                {
                    case 0:
                        r = v; g = t; b = p;
                        break;
                    case 1:
                        r = q; g = v; b = p;
                        break;
                    case 2:
                        r = p; g = v; b = t;
                        break;
                    case 3:
                        r = p; g = q; b = v;
                        break;
                    case 4:
                        r = t; g = p; b = v;
                        break;
                    default:
                        r = v; g = p; b = q;
                        break;
                }
            }
            
            data[pos] = (unsigned char)r;
            data[pos + 1] = (unsigned char)g;
            data[pos + 2] = (unsigned char)b;
        }
    }
    
    return true;
}
