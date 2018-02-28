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

int main(int argc, const char * argv[]) {
    
    /*ChessPattern();
    
    InvertRGB();
    
    InvertGrayScale();*/
    
    RGBToHSV();
    
    return 0;
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
