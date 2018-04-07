//
//  main.c
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 21/02/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

#ifdef OSX
#include "Engine.h"
#include "Filters.h"
#include "main.h"
#include "Conversors.h"
#include "Segmentators.h"
#include "Engine/Labeling/Labeling.h"
#else
#include "../VisaoComputador/Engine/Engine.h"
#include "../VisaoComputador/Engine/Filters.h"
#include <stdlib.h>
#include "main.h"
#include "../VisaoComputador/Engine/Conversors/Conversors.h"
#include "../VisaoComputador/Engine/Segmentators.h"
#include "../VisaoComputador/Engine/Labeling/Labeling.h"
#endif



int main(int argc, const char * argv[]) 
{
	setlocale(LC_ALL, "pt_PT");
	Image *originalImage = vc_read_image("../../VisaoComputador/Images/PecasDeMadeira.ppm");
	Image *hsvImage = vc_read_image("../../VisaoComputador/Images/PecasDeMadeira.ppm");
	Image *grayImage = NULL;
	Image *binaryImage = NULL;

	if(originalImage == NULL)
	{
		printf("ERRO -> IMAGEM NAO ENCONTRADA");
		getchar();
		return 0;
	}

	ConvertRBGToHSVWithSaturation(hsvImage);
	//vc_write_image("../../VisaoComputador/Results/hsv.pgm", hsvImage);
    
	grayImage = vc_image_new(hsvImage->width, hsvImage->height, 1, hsvImage->levels);
	
	if (ConvertRGBToGrayScaleBasedOnChannel(hsvImage, grayImage, false, true, false))
	{
		vc_write_image("../../VisaoComputador/Results/grayImage.pgm", grayImage);

		binaryImage = vc_read_image("../../VisaoComputador/Results/grayImage.pgm");

		ApplyGrayScaleToBinary(binaryImage, 50);
		vc_write_image("../../VisaoComputador/Results/binary.pgm", binaryImage);
	}
    
	vc_image_free(originalImage);

	printf("Pressione enter para continuar...\n");
	getchar();
}

void TP1Dados()
{
    Image *image = vc_read_image("Images/Dados.ppm");
    if (image == NULL)
    {
        printf("ERROR!");
        getchar();
    }
    
    Image *grayImage = vc_image_new(image->width, image->height, 1, image->levels);
    
    if (ConvertRGBToGrayScaleBasedOnChannel(image, grayImage, false, true, false))
    {
        //First Pass 2 Pieces (White)
        vc_write_image("grayImage.pgm", grayImage);
        
        Image *binaryImage = vc_read_image("grayImage.pgm");
        
        ApplyGrayScaleToBinary(binaryImage, 193);
        vc_write_image("binary.pgm", binaryImage);
        
        int i, nblobs;
        Blob *blobs;
        
        Image *blobsOutputImage = vc_image_new(binaryImage->width, binaryImage->height, 1, 255);
        if(blobsOutputImage == NULL)
        {
            printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
            getchar();
        }
        
        blobs = GetBlobArrayFromImage(binaryImage, blobsOutputImage, &nblobs);
        
        if(blobs != NULL)
        {
            FillBlobsInfoFromImage(blobsOutputImage, blobs, nblobs);
            
            printf("\nNumber of segmented objects: %d\n", nblobs);
            for(i=0; i<nblobs; i++)
            {
                if(blobs[i].area > 700) {
                    printf("\n-> Label %d:\n", blobs[i].label);
                    printf("   Area=%-5d Perimetro=%-5d x=%-5d y=%-5d w=%-5d h=%-5d xc=%-5d yc=%-5d\n", blobs[i].area, blobs[i].perimeter, blobs[i].x, blobs[i].y, blobs[i].width, blobs[i].height, blobs[i].xc, blobs[i].yc);
                }
            }
        }
        
        vc_write_image("blobsOutputImage.pgm", blobsOutputImage);
        
        vc_image_free(blobsOutputImage);
        
        
        /*Image *morphImage = vc_image_new(image->width, image->height, 1, image->levels);
        if (ApplyBinaryErode(grayImage, morphImage, 10))
        {
            Image *morphImage2 = vc_image_new(image->width, image->height, 1, image->levels);
            ApplyBinaryDilate(morphImage, morphImage2, 30);
            vc_write_image("morphImage.pgm", morphImage);
            vc_write_image("morphImageComplete.pgm", morphImage2);
            vc_image_free(morphImage);
            vc_image_free(morphImage2);
        }*/
        
        /*
        //Second Pass 1 Piece (Black)
        ApplyInvertGrayScale(grayImage);
        
        vc_write_image("grayImage2.pgm", grayImage);
        
        ApplyGrayScaleToBinary(grayImage, 10);
        
        vc_write_image("binary2.pgm", grayImage);
        
        LabelingTP1();
         */
        
        vc_image_free(grayImage);
    }
    
    vc_image_free(image);
    
    /*if (ApplyBinaryErode(image, output, 10))
    {
        vc_write_image("output.pgm", output);
        
        vc_image_free(image);
        vc_image_free(output);
        
        printf("press any key...");
        getchar();
    }*/
}

void LabelingTP1()
{
    Image *image[2];
    int i, nblobs;
    Blob *blobs;
    
    image[0] = vc_read_image("binary.pgm");
    
    if(image[0] == NULL)
    {
        printf("ERROR -> vc_read_image():\n\tFile not found!\n");
        getchar();
    }
    
    image[1] = vc_image_new(image[0]->width, image[0]->height, 1, 255);
    if(image[1] == NULL)
    {
        printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
        getchar();
    }
    
    blobs = GetBlobArrayFromImage(image[0], image[1], &nblobs);
    
    if(blobs != NULL)
    {
        FillBlobsInfoFromImage(image[1], blobs, nblobs);
        
        printf("\nNumber of segmented objects: %d\n", nblobs);
        for(i=0; i<nblobs; i++)
        {
            if(blobs[i].area > 700) {
                printf("\n-> Label %d:\n", blobs[i].label);
                printf("   Area=%-5d Perimetro=%-5d x=%-5d y=%-5d w=%-5d h=%-5d xc=%-5d yc=%-5d\n", blobs[i].area, blobs[i].perimeter, blobs[i].x, blobs[i].y, blobs[i].width, blobs[i].height, blobs[i].xc, blobs[i].yc);
            }
        }
    }
    
    vc_write_image("vc0023.pgm", image[1]);
    
    vc_image_free(image[1]);
    
    //system("FilterGear vc0023.pgm");
    
    printf("Press any key to exit...\n");
    getchar();
}

void Labeling()
{
    Image *image[2];
    int i, nblobs;
    Blob *blobs;
    
    image[0] = vc_read_image("Images/coins.pgm");
    
    if(image[0] == NULL)
    {
        printf("ERROR -> vc_read_image():\n\tFile not found!\n");
        getchar();
    }
    
    image[1] = vc_image_new(image[0]->width, image[0]->height, 1, 255);
    if(image[1] == NULL)
    {
        printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
        getchar();
    }
    
    ApplyInvertGrayScale(image[0]);
    ApplyGrayScaleToBinary(image[0], 127);
    blobs = GetBlobArrayFromImage(image[0], image[1], &nblobs);
    
    if(blobs != NULL)
    {
        FillBlobsInfoFromImage(image[1], blobs, nblobs);
        
        printf("\nNumber of segmented objects: %d\n", nblobs);
        for(i=0; i<nblobs; i++)
        {
            if(blobs[i].area > 700) {
                printf("\n-> Label %d:\n", blobs[i].label);
                printf("   Area=%-5d Perimetro=%-5d x=%-5d y=%-5d w=%-5d h=%-5d xc=%-5d yc=%-5d\n", blobs[i].area, blobs[i].perimeter, blobs[i].x, blobs[i].y, blobs[i].width, blobs[i].height, blobs[i].xc, blobs[i].yc);
            }
        }
    }
    
    vc_write_image("vc0023.pgm", image[1]);
    vc_write_image("vc0021.pgm", image[0]);
    
    vc_image_free(image[0]);
    vc_image_free(image[1]);
    
    //system("FilterGear vc0023.pgm");
    
    printf("Press any key to exit...\n");
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
    
    //CreateChessPattern(image);
    
    vc_write_image("output.pbm", image);
    vc_image_free(image);
    
    return 1;
}
