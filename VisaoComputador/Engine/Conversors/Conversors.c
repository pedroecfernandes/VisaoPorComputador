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
#include "Conversors.h"
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "../Utils.h"
#include "../Engine.h"
#endif
#include "../Segmentators.h"


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

bool ConvertRGBToGrayScale(Image *image, Image *output)
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

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			posRGB = y * bytesperlineRGB + x * channels;
			posGray = y * bytesperlineGray + x * output->channels;

			r = (float)data[posRGB];
			g = (float)data[posRGB + 1];
			b = (float)data[posRGB + 2];

			output->data[posGray] = (r + g + b) / 3;
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
    float s = 0.0, h = 0.0, v = 0.0;
    float r = 0.0, g = 0.0, b = 0.0;
    
    if ((width <= 0) || (height <= 0) || (image->data == NULL)) return false;
    if (channels != 3) return 0;

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
            pos = y * bytesperline + x * channels;
			
            r = (float)data[pos];
            g = (float)data[pos + 1];
            b = (float)data[pos + 2];
            
            max = Max3(r, g, b);
			min = Min3(r, g, b);

			v = max;
			if (v == 0)
			{
				h = 0;
				s = 0;
			}
			else
			{

				s = 255 * (max - min) / v;
				if (s == 0)
				{
					h = 0;
				}
				else
				{

					if (max == r)
						h = 0 + 43 * (g - b) / (max - min);
					else if (max == g)
						h = 85 + 43 * (b - r) / (max - min);
					else
						h = 171 + 43 * (r - g) / (max - min);
				}
			}

            
            data[pos] = (unsigned char)h;
			data[pos + 1] = (unsigned char)s;
			data[pos + 2] = (unsigned char)v;
        }
    }
    
    return true;
}

<<<<<<< HEAD
bool ConvertHSVToBinary(Image *image, Image *binaryImage, int threshold)
{
	unsigned char *data = (unsigned char *)image->data;
	int width = image->width;
	int height = image->height;
	int bytesperline = image->width*image->channels;
	int bytesperlineGray = binaryImage->width*binaryImage->channels;
	int channels = image->channels;
	int x, y;
	long int pos;
	long int posBinary;
	unsigned char s = 0.0;

	if ((width <= 0) || (height <= 0) || (image->data == NULL)) return false;
	if (channels != 3) return 0;

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
			pos = y * bytesperline + x * channels;
			posBinary = y * bytesperlineGray + x * binaryImage->channels;

			s = (float)data[pos + 1];

			if (s < threshold)
			{
				binaryImage->data[posBinary] = 0.0f;
			}
			else
			{
				binaryImage->data[posBinary] = 255.0f;
			}
		}
	}

	return true;
=======
bool ConvertHSVToRGB(Image *image)
{
    unsigned char *data = (unsigned char *)image->data;
    int width = image->width;
    int height = image->height;
    int bytesperline = image->width*image->channels;
    int channels = image->channels;
    int x, y;
    long int pos;
    float max = 0, min = 255;
    unsigned char s = 0.0, h = 0.0, v = 0.0;
    float r = 0.0, g = 0.0, b = 0.0;
    unsigned char region, remainder, p, q, t;
    
    if ((width <= 0) || (height <= 0) || (image->data == NULL)) return false;
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
>>>>>>> 995d97458ee33e719337384e750cdc876242d693
}
