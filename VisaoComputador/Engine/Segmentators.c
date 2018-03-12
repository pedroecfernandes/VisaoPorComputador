//
//  Segmentators.c
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 07/03/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//


#ifdef OSX

#include "Segmentators.h"

#else
// TODO: Márcio
#endif


bool ApplyGrayScaleBinaryThreshold(Image *image, int threshold)
{
    unsigned char *data = (unsigned char *)image->data;
    int width = image->width;
    int height = image->height;
    int bytesperline = image->width*image->channels;
    int channels = image->channels;
    int x, y;
    long int pos;
    
    if ((width <= 0) || (height <= 0) || (image->data == NULL)) return false;
    if (channels != 1) return false;
    
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            pos = y * bytesperline + x * channels;
            if (data[pos] < threshold)
            {
                data[pos] = 0;
            }
            else
            {
                data[pos] = 255;
            }
        }
    }
    return true;
}

bool ApplyGrayScaleBinaryMidpoint(Image *input, Image *output, int kernel)
{
    unsigned char *datasrc = (unsigned char *)input->data;
    unsigned char *datadst = (unsigned char *)output->data;
    int width = input->width;
    int height = input->height;
    int bytesperline = input->bytesperline;
    int channels = input->channels;
    int x, y;
    int xx, yy;
    int xxyymax = (kernel - 1) / 2;
    int xxyymin = -xxyymax;
    int max, min;
    long int pos, posk;
    unsigned char threshold;
    
    if ((input->width <= 0) || (input->height <= 0) || (input->data == NULL))
        return false;
    if ((input->width != output->width) || (input->height != output->height) || (input->channels != output->channels)) return false;
    if (channels != 1)
        return false;
    
    for (y = 0; y<height; y++)
    {
        for (x = 0; x<width; x++)
        {
            pos = y * bytesperline + x * channels;
            
            max = datasrc[pos];
            min = datasrc[pos];
            
            // NxM Vizinhos
            for (yy = xxyymin; yy <= xxyymax; yy++)
            {
                for (xx = xxyymin; xx <= xxyymax; xx++)
                {
                    if ((y + yy >= 0) && (y + yy < height) && (x + xx >= 0) && (x + xx < width))
                    {
                        posk = (y + yy) * bytesperline + (x + xx) * channels;
                        
                        if (datasrc[posk] > max) max = datasrc[posk];
                        if (datasrc[posk] < min) min = datasrc[posk];
                    }
                }
            }
            
            threshold = (unsigned char)((float)(max + min) / (float)2);
            
            if (datasrc[pos] > threshold) datadst[pos] = 255;
            else datadst[pos] = 0;
        }
    }
    
    return true;
}

bool ApplyBinaryDilate(Image *input, Image *output, int kernel)
{
    unsigned char *datasrc = (unsigned char *)input->data;
    unsigned char *datadst = (unsigned char *)output->data;
    int width = input->width;
    int height = input->height;
    int bytesperline = input->bytesperline;
    int channels = input->channels;
    int x, y;
    int xx, yy;
    int xxyymax = (kernel - 1) / 2;
    int xxyymin = -xxyymax;
    int max, min;
    long int pos, posk;
    int aux = 0;
    // Verificação de erros
    if ((input->width <= 0) || (input->height <= 0) || (input->data == NULL))
        return false;
    if ((input->width != output->width) || (input->height != output->height) || (input->channels != output->channels)) return false;
    if (channels != 1)
        return false;
    
    for (y = 0; y<height; y++)
    {
        for (x = 0; x<width; x++)
        {
            pos = y * bytesperline + x * channels;
            
            max = datasrc[pos];
            min = datasrc[pos];
            aux = 0;
            // NxM Vizinhos
            for (yy = xxyymin; yy <= xxyymax; yy++)
            {
                for (xx = xxyymin; xx <= xxyymax; xx++)
                {
                    if ((y + yy >= 0) && (y + yy < height) && (x + xx >= 0) && (x + xx < width))
                    {
                        posk = (y + yy) * bytesperline + (x + xx) * channels;
                        
                        if (datasrc[posk] == 255)
                            aux = 255;
                    }
                }
            }
            
            datadst[pos] = aux;
        }
    }
    
    return true;
}

bool ApplyBinaryErode(Image *input, Image *output, int kernel)
{
    unsigned char *datasrc = (unsigned char *)input->data;
    unsigned char *datadst = (unsigned char *)output->data;
    int width = input->width;
    int height = input->height;
    int bytesperline = input->bytesperline;
    int channels = input->channels;
    int x, y;
    int xx, yy;
    int xxyymax = (kernel - 1) / 2;
    int xxyymin = -xxyymax;
    int max, min;
    long int pos, posk;
    int aux = 255;
    
    if ((input->width <= 0) || (input->height <= 0) || (input->data == NULL))
        return false;
    if ((input->width != output->width) || (input->height != output->height) || (input->channels != output->channels))
        return false;
    if (channels != 1)
        return false;
    
    for (y = 0; y<height; y++)
    {
        for (x = 0; x<width; x++)
        {
            pos = y * bytesperline + x * channels;
            
            max = datasrc[pos];
            min = datasrc[pos];
            aux = 255;
            // NxM Vizinhos
            for (yy = xxyymin; yy <= xxyymax; yy++)
            {
                for (xx = xxyymin; xx <= xxyymax; xx++)
                {
                    if ((y + yy >= 0) && (y + yy < height) && (x + xx >= 0) && (x + xx < width))
                    {
                        posk = (y + yy) * bytesperline + (x + xx) * channels;
                        
                        if (datasrc[posk] == 0)aux = 0;
                    }
                }
            }
            
            datadst[pos] = aux;
            
            
        }
    }
    
    return true;
}
