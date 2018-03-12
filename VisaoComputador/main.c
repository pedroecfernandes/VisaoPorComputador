//
//  main.c
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 21/02/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include "Engine.h"
#include "Filters.h"
#include <stdbool.h>
#include "main.h"
#include "Conversors.h"
#include "Segmentators.h"

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
    
    ApplyGrayBinaryDilate();
    
    return 0;
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
    
    if (ApplyGrayScaleBinaryThreshold(image, 160))
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
