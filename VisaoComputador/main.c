//
//  main.c
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 21/02/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS 


#ifdef OSX
#include <stdio.h>
#include "Engine.h"
#include "Filters.h"
#include <stdbool.h>
#include "main.h"
#include "Conversors.h"
#include "Segmentators.h"
#include "Engine/Labeling/Labeling.h"
#else
#include <stdio.h>
#include "../VisaoComputador/Engine/Engine.h"
#include "../VisaoComputador/Engine/Filters.h"
#include <stdbool.h>
#include "main.h"
#include "../VisaoComputador/Engine/Conversors/Conversors.h"
#include "../VisaoComputador/Engine/Segmentators.h"
#include "../VisaoComputador/Engine/Labeling/Labeling.h" //TODO: Márcio
#endif



int main(int argc, const char * argv[]) {
    
    /*ChessPattern();
    
    InvertRGB();
    
    InvertGrayScale();*/
    
    //RGBToHSV();
    
    //RGBToGrayScaleBasedOnRedChannel();
    
    //RGBToBGR();
    
    //ApplyGrayBinarySegmentation();
    
    //ApplyGrayBinaryMidpointSegmentation();
    
    //ApplyGrayBinaryErode();
    
    //ApplyGrayBinaryDilate();
    
    Labeling();
    
    return 0;
}

int vc_binary_blob_labellingMeu(Image *src, Image *dst) {
    unsigned char *data = (unsigned char *)src->data;
    int width = src->width;
    int height = src->height;
    int byteperline = src->width*src->channels;
    int channels = src->channels;
    int x, y;
    long int pos;
    long int posA, posB, posC, posD;
    unsigned char table[256];
    int label = 1;
    
    if ((width <= 0) || (height <= 0) || (src->data == NULL)) return 0;
    if (channels != 1) return 0;
    
    for (int i = 0; i <= 255; i++)
    {
        table[i] = i;
    }
    
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width;x++)
        {
            pos = y * byteperline + x * channels;
            dst->data[pos] = 0;
        }
    }
    
    for (y = 0; y < height; y++)
    {
        pos = y * byteperline + 0 * channels;
        
        data[pos] = 0;
    }
    for (y = 0; y < height; y++)
    {
        pos = y * byteperline + (width -1) * channels;
        
        data[pos] = 0;
    }
    
    for (x = 0; x < width; x++)
    {
        pos = 0 * byteperline + x * channels;
        
        data[pos] = 0;
    }
    for (x = 0; x < width; x++)
    {
        pos = (height - 1) * byteperline + x * channels;
        
        data[pos] = 0;
    }
    
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width;x++)
        {
            pos = y * byteperline + x * channels;
            if (data[pos] == 255) {
                posA = (y - 1)* byteperline + (x - 1) * channels;
                posB = (y - 1)* byteperline + (x)* channels;
                posC = (y - 1)* byteperline + (x + 1)* channels;
                posD = (y)* byteperline + (x - 1)* channels;
                
                if ((dst->data[posA] == 0) && (dst->data[posB] == 0) && (dst->data[posC] == 0) && (dst->data[posD] == 0))
                {
                    dst->data[pos] = label;
                    label++;
                }
                else
                {
                    if ((dst->data[posA] < dst->data[posB]) && (dst->data[posA] > 0) && (dst->data[posA] < dst->data[posC]) && (dst->data[posA] < dst->data[posD]))
                        dst->data[pos] = dst->data[posA];
                    else if ((dst->data[posB] < dst->data[posC]) && (dst->data[posB] > 0) && (dst->data[posB] < dst->data[posD]))
                        dst->data[pos] = dst->data[posB];
                    else if  (dst->data[posC] < dst->data[posD] && (dst->data[posC] > 0))
                        dst->data[pos] = dst->data[posC];
                    else
                        dst->data[pos] = dst->data[posD];
                }
            }
        }
    }
    
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width;x++)
        {
            pos = y * byteperline + x * channels;
            posA = (y - 1)* byteperline + (x - 1) * channels;
            posB = (y - 1)* byteperline + (x)* channels;
            posC = (y - 1)* byteperline + (x + 1)* channels;
            posD = (y)* byteperline + (x - 1)* channels;
            if ((pos > 0) && (pos < 255)) {
                if ((dst->data[posA] <= dst->data[posB]) && (dst->data[posA] <= dst->data[posC]) && (dst->data[posA] <= dst->data[posD])) {
                    for (int i = 0; i <= 255; i++)
                    {
                        if(table[i] == table[posA])
                            table[posA] = dst->data[posA];
                    }
                }
                else if ((dst->data[posB] <= dst->data[posC]) && (dst->data[posB] <= dst->data[posD]))
                    table[posB] = table[pos];
                
                else if (dst->data[posC] <= dst->data[posD])
                    table[posC] = table[pos];
                
                else
                    table[posD] = table[pos];
            }
        }
    }
    return 1;
}

void Labeling()
{
    Image * image[2];
    int i, nblobs;
    Blob *blobs;
    
    image[0] = vc_read_image("Images/coins.pgm");
    
    
    if (image[0] == NULL) {
        printf("ERROR -> vc_read_image():\n\tFile not found!\n");
        getchar();
    }
    
    image[1] = vc_image_new(image[0]->width, image[0]->height, 1, 255);
    if (image[1] == NULL) {
        printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
        getchar();
    }
    
    ApplyGrayScaleToBinary(image[0], 127);
    blobs = GetBlobArrayFromImage(image[0], image[1], &nblobs);
    
    if (blobs != NULL) {
        printf("\nNumber of labels: %d\n", nblobs);
        for (i = 0; i < nblobs; i++) {
            printf("-> Label %d\n", blobs[i].label);
        }
    }
    
    vc_write_image("output.pgm", image[1]);
    
    vc_image_free(image[0]);
    vc_image_free(image[1]);

    
    
    
    
    printf("press any key...");
    getchar();
    
}

void ApplyGrayBinaryErode()
{
    Image *image = vc_read_image("Images/flir-04.pgm");
    if (image == NULL)
    {
        printf("ERROR!");
        getchar();
    }
    
    Image *output = vc_image_new(image->width, image->height, image->channels, image->channels);
    
    if (ApplyBinaryErode(image, output, 10))
    {
        vc_write_image("output.pgm", output);
        
        vc_image_free(image);
        vc_image_free(output);
        
        printf("press any key...");
        getchar();
    }
}

void ApplyGrayBinaryDilate()
{
    Image *image = vc_read_image("Images/flir-04.pgm");
    if (image == NULL)
    {
        printf("ERROR!");
        getchar();
    }
    
    Image *output = vc_image_new(image->width, image->height, image->channels, image->channels);
    
    if (ApplyBinaryDilate(image, output, 15))
    {
        vc_write_image("output.pgm", output);
        
        vc_image_free(image);
        vc_image_free(output);
        
        printf("press any key...");
        getchar();
    }
}

void ApplyGrayBinaryMidpointSegmentation()
{
    Image *image = vc_read_image("Images/flir-04.pgm");
    if (image == NULL)
    {
        printf("ERROR!");
        getchar();
    }
    
    Image *output = vc_image_new(image->width, image->height, image->channels, image->channels);
    
    if (ApplyGrayScaleBinaryMidpoint(image, output, 160))
    {
        vc_write_image("output.pgm", output);
        
        vc_image_free(image);
        vc_image_free(output);
        
        printf("press any key...");
        getchar();
    }
}

void ApplyGrayBinarySegmentation()
{
    Image *image = vc_read_image("Images/flir-04.pgm");
    if (image == NULL)
    {
        printf("ERROR!");
        getchar();
    }
    
    if (ApplyGrayScaleToBinary(image, 160))
    {
        vc_write_image("output.pgm", image);
        
        vc_image_free(image);
        
        printf("press any key...");
        getchar();
    }
}

void RGBToBGR()
{
    Image *image = vc_read_image("Images/HSVTestImage01.ppm");
    if (image == NULL)
    {
        printf("ERROR!");
        getchar();
    }
    
    if (ConvertRGBToBGR(image))
    {
        vc_write_image("output.ppm", image);
        
        vc_image_free(image);
        
        printf("press any key...");
        getchar();
    }
}

void RGBToGrayScaleBasedOnRedChannel()
{
    Image *image = vc_read_image("Images/HSVTestImage01.ppm");
    if (image == NULL)
    {
        printf("ERROR!");
        getchar();
    }
    
    Image *output = vc_image_new(image->width, image->height, 1, 255);
    
    if (ConvertRGBToGrayScaleBasedOnChannel(image, output, false, false, true))
    {
        vc_write_image("output.pbm", output);
    }
    
    vc_image_free(image);
    vc_image_free(output);
    
    printf("press any key...");
    getchar();
}

void RGBToHSV()
{
    Image *image = vc_read_image("Images/HSVTestImage02.ppm");
    if (image == NULL)
    {
        printf("ERROR!");
        getchar();
    }
    
    if (ConvertRBGToHSV(image))
    {
        vc_write_image("output.ppm", image);
        
        vc_image_free(image);
        
        printf("press any key...");
        getchar();
    }
}


void InvertRGB()
{
    Image *image = vc_read_image("Images/hell.ppm");
    if (image == NULL)
    {
        printf("ERROR!");
        getchar();
    }
    
    if (ApplyInvertRGB(image))
    {
        vc_write_image("output.ppm", image);
        
        vc_image_free(image);
        
        printf("press any key...");
        getchar();
    }
}

void InvertGrayScale()
{
    Image *image = vc_read_image("Images/flir-01.pgm");
    if (image == NULL)
    {
        printf("ERROR!");
        getchar();
    }
    
    if (ApplyInvertGrayScale(image))
    {
        vc_write_image("output.pgm", image);
        
        vc_image_free(image);
        
        printf("press any key...");
        getchar();
    }
}

int ChessPattern()
{
    Image *image = vc_image_new(320, 280, 1, 1);
    
    if (image == NULL)
    {
        printf("Error!");
        getchar();
        return 0;
    }
    
    CreateChessPattern(image);
    
    vc_write_image("output.pbm", image);
    vc_image_free(image);
    
    return 1;
}
