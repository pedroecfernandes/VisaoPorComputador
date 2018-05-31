//
//  teste.cpp
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 21/05/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//

#ifdef OSX
#include <stdio.h>
#include <stdbool.h>
#include "Conversors.hpp"
#include "Segmentators.hpp"
#include "Filters.hpp"
#include <math.h>
#include "Engine/Labeling/Labeling.hpp"
#else
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "Engine/Conversors/Conversors.hpp"
#include "Engine/Segmentators.hpp"
#include "Engine/Labeling/Labeling.hpp"
#include "TP2.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>
#endif

double GetCircleArea(int r)
{
    return M_PI * (r * r);
}

void CountDarkCoins(double area, int &one, int &two, int &five)
{
    if (area > GetCircleArea(55) && area <GetCircleArea(64))
    {
        one++;
        printf("One!");
    }
    else if (area > GetCircleArea(66) && area <GetCircleArea(70))
    {
        two++;
        printf("Two!");
    }
    else if (area > GetCircleArea(72) && area <GetCircleArea(80))
    {
        five++;
        printf("Five!");
    }
}

void CountGoldCoins(double area, int &ten, int &twenty, int &fifty)
{
    //TODO:
    if (area > GetCircleArea(55) && area <GetCircleArea(64))
    {
        ten++;
    }
    else if (area > GetCircleArea(66) && area <GetCircleArea(70))
    {
        twenty++;
    }
    else if (area > GetCircleArea(72) && area <GetCircleArea(80))
    {
        fifty++;
    }
}

void CountMixedCoins(double area, int &one, int &two)
{
    //TODO:
    if (area > GetCircleArea(55) && area <GetCircleArea(64))
    {
        one++;
    }
    else if (area > GetCircleArea(66) && area <GetCircleArea(70))
    {
        two++;
    }
}

int main(int argc, const char * argv[])
{
    std::cout << "OpenCV Version" << CV_VERSION << std::endl;
    
    // Vídeo
    char *videofile = (char*)"Images/video3-tp2.mp4";
    CvCapture *capture;
    IplImage *frame;
    Blob *activeFrameBlobs = NULL;
    int nActiveFrameBlobs = 0;
    Blob *previousFrameBlobs = NULL;
    int nPreviousFrameBlobs = 0;
    IplImage *blobsFullImage = NULL;
    int i = 0;
    struct
    {
        int width, height;
        int ntotalframes;
        int fps;
        int nframe;
    } video;
    // Texto
    CvFont font, fontbkg;
    double hScale = 0.5;
    double vScale = 0.5;
    int lineWidth = 1;
    char str[500] = { 0 };
    // Outros
    int key = 0;
    IplImage *gray = NULL;
    IplImage *binaryEroded = NULL;
    int c1 = 0, c2 = 0, c5 = 0, c10 = 0, c20 = 0, c50 = 0, c100 = 0, c200 = 0;
    
    /* Leitura de vídeo de um ficheiro */
    capture = cvCaptureFromFile(videofile);
    
    /* Verifica se foi possível abrir o ficheiro de vídeo */
    if (!capture)
    {
        fprintf(stderr, "Erro ao abrir o ficheiro de vídeo!\n");
        return 1;
    }
    
    /* Número total de frames no vídeo */
    video.ntotalframes = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
    /* Frame rate do vídeo */
    video.fps = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
    /* Resolução do vídeo */
    video.width = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
    video.height = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
    
    /* Cria uma janela para exibir o vídeo */
    cvNamedWindow("VC - TP2", CV_WINDOW_AUTOSIZE);
    
    /* Inicializa a fonte */
    cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, hScale, vScale, 0, lineWidth);
    cvInitFont(&fontbkg, CV_FONT_HERSHEY_SIMPLEX, hScale, vScale, 0, lineWidth + 1);
    
    while (key != 'q') {
        /* Leitura de uma frame do vídeo */
        frame = cvQueryFrame(capture);
        
        /* Verifica se conseguiu ler a frame */
        if (!frame) break;
        
        /* Número da frame a processar */
        video.nframe = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES);
        
        /* Exemplo de inserção texto na frame */
        sprintf(str, "RESOLUCAO: %dx%d", video.width, video.height);
        cvPutText(frame, str, cvPoint(20, 20), &fontbkg, cvScalar(0, 0, 0));
        cvPutText(frame, str, cvPoint(20, 20), &font, cvScalar(255, 255, 255));
        sprintf(str, "TOTAL DE FRAMES: %d", video.ntotalframes);
        cvPutText(frame, str, cvPoint(20, 40), &fontbkg, cvScalar(0, 0, 0));
        cvPutText(frame, str, cvPoint(20, 40), &font, cvScalar(255, 255, 255));
        sprintf(str, "FRAME RATE: %d", video.fps);
        cvPutText(frame, str, cvPoint(20, 60), &fontbkg, cvScalar(0, 0, 0));
        cvPutText(frame, str, cvPoint(20, 60), &font, cvScalar(255, 255, 255));
        sprintf(str, "N. FRAME: %d", video.nframe);
        cvPutText(frame, str, cvPoint(20, 80), &fontbkg, cvScalar(0, 0, 0));
        cvPutText(frame, str, cvPoint(20, 80), &font, cvScalar(255, 255, 255));
        
        // Faça o seu código aqui...
        
        //frame->
        
        if (blobsFullImage == NULL)
            blobsFullImage = cvCreateImage(cvGetSize(frame), 8, 1); // allocate a 1 channel byte image
        if (gray == NULL)
            gray = cvCreateImage(cvGetSize(frame), 8, 1); // allocate a 1 channel byte image
        if (binaryEroded == NULL)
            binaryEroded = cvCreateImage(cvGetSize(frame), 8, 1); // allocate a 1 channel byte image
        
        ConvertRGBToGrayScaleBasedOnChannel(frame, gray, 1, 0, 0);
        ApplyInvertGrayScale(gray);
        ApplyGrayScaleToBinary(gray, 130);
        ApplyBinaryErode(gray, binaryEroded, 3);
        //cvSaveImage("binary.png", gray);
        //cvSaveImage("binaryEroded.png", binaryEroded);
        
        activeFrameBlobs = GetBlobArrayFromImage(binaryEroded, blobsFullImage, &nActiveFrameBlobs);
        FillBlobsInfoFromImage(blobsFullImage, activeFrameBlobs, nActiveFrameBlobs);
    
        for(i = 0; i < nActiveFrameBlobs; i++)
        {
            // BEGIN check for repeated blob & ignore
            
            if (video.height - (activeFrameBlobs[i].y + activeFrameBlobs[i].height) <= 50)
                continue;
            
            bool found = false;
            
            for (int j = 0; j < nPreviousFrameBlobs; j++)
            {
                if (video.height - (previousFrameBlobs[j].y + previousFrameBlobs[j].height) < 50)
                    continue;
                
                double blobsDistance = sqrt(pow(abs(activeFrameBlobs[i].xc - previousFrameBlobs[j].xc), 2) + pow(abs(activeFrameBlobs[i].yc - previousFrameBlobs[j].yc), 2));
                if (blobsDistance < 50)
                {
                    found = true;
                    break;
                }
            }

            // END check for repeated blob & ignore
            
            
            if (!found)
            {
                // BEGIN image processing
                
                //IplImage* extractedCoinImage = cvCreateImage(cvSize(blobs[i].width, blobs[i].height), 8, 3); // allocate a 3 channel byte image
                
                //ExtractImageFromBlob(blobs[i], frame, extractedCoinImage);
                
                //cvSaveImage("coin.png", extractedCoinImage);
                
                //ConvertBGRToHSV(extractedCoinImage);
                
                //TODO: Check in extractedCoinImage HSV dominant color in original image (calc all points and make medium)
                //int h = 0, s = 0, v = 0;
                
                //TODO:
                //GetMediumHSVColorsFromBlobExtratedImage(blob, extractedCoinImage, h, s, v);
                
                // Dark Coins
                //if (s > 40 && v > 25 && (h > 19 && h < 22))
                //{
                
                // Only start counting when blob is full on screen :)
                CountDarkCoins(activeFrameBlobs[i].area, c1, c2, c5);
                
                //CountGoldCoins(blobs[i].area, c10, c20, c50);
                //CountMixedCoins(blobs[i].area, c100, c200);
                
                //cvReleaseImage(&extractedCoinImage);
                
                // END image processing
            }
        }
        
        free(previousFrameBlobs);
        free(activeFrameBlobs);
    
        
        previousFrameBlobs = GetBlobArrayFromImage(binaryEroded, blobsFullImage, &nPreviousFrameBlobs);
        FillBlobsInfoFromImage(blobsFullImage, previousFrameBlobs, nPreviousFrameBlobs);
        
        cvReleaseImage(&blobsFullImage);
        cvReleaseImage(&gray);
        cvReleaseImage(&binaryEroded);
        
        /* Exibe a frame */
        cvShowImage("VC - TP2", frame);
        
        /* Sai da aplicação, se o utilizador premir a tecla 'q' */
        key = cvWaitKey(1);
    }
    
    /* Fecha a janela */
    cvDestroyWindow("VC - TP2");
    
    /* Fecha o ficheiro de vídeo */
    cvReleaseCapture(&capture);
    
    return 0;
}
