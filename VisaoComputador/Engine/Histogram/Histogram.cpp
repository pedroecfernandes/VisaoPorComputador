//
////
////  Histogram.c
////  VisaoComputador
////
////  Created by Pedro C. Fernandes on 30/04/18.
////  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
////
//
//#include "Histogram.hpp"
//
//
//bool GetHistogram(Image *src, Image *dst)
//{
//    unsigned char *data = (unsigned char *)src->data;
//    int width = src->width;
//    int height = src->height;
//    int bytesperline = src->width*src->channels;
//    int channels = src->channels;
//    int x, y,i;
//    long int pos;
//    int contapixeis[256] = { 0 };
//    float pdf[256];
//    float temp;
//    float max = 0;
//    
//    if ((width <= 0) || (height <= 0) || (src->data == NULL)) return 0;
//    if (channels != 1) return 0;
//    
//    for (y = 0; y < height; y++)
//    {
//        for (x = 0; x < width;x++)
//        {
//            pos = y * bytesperline + x * channels;
//            
//            contapixeis[data[pos]]++;
//        }
//    }
//    
//    for (i = 0; i < 256; i++)
//    {
//        pdf[i] = (float)((float)contapixeis[i] / (float)(width*height));
//        if (pdf[i] > max)
//            max = pdf[i];
//    }
//    
//    for (x = 0; x < dst->width;x++)
//    {
//        temp = ((pdf[x] * (float)255) / max);
//        for (y = 255; y >= 0; y--)
//        {
//            pos = y * dst->bytesperline + x * dst->channels;
//            
//            if (temp >= (float)((float)(255) - (float)y))
//                dst->data[pos] = (unsigned char)255;
//            else
//                dst->data[pos] = (unsigned char)0;
//        }
//    }
//    
//    return 1;
//}
//
//
//bool GetHistogramGrayScale(Image *src, Image *dst)
//{
//    unsigned char *data = (unsigned char *)src->data;
//    int width = src->width;
//    int height = src->height;
//    int byteperline = src->width*src->channels;
//    int channels = src->channels;
//    int x, y;
//    long int pos;
//    int contarpixeis[256] = { 0 };
//    float pdf[256];
//    float conta = 0;
//    float max = 0;
//    double temp;
//    float cdf[256] = { 0 };
//    float equalizacao[256] = { 0 };
//    
//    
//    
//    if ((src->width <= 0) || (src->height <= 0) || (src->data == NULL))
//        return 0;
//    if (channels != 1)
//        return 0;
//    
//    //numero pixeis repetidos
//    for (y = 0;y<height;y++)
//    {
//        for (x = 0;x<width;x++)
//        {
//            pos = y*byteperline + x*channels;
//            contarpixeis[(int)data[pos]]++;
//        }
//    }
//    
//    //clacula pdf
//    for (y = 0;y<256;y++)
//    {
//        pdf[y] = (float)contarpixeis[y] / (float)(width*height);
//        conta += pdf[y];
//        
//        if (max<pdf[y])
//            max = pdf[y];
//    }
//    
//    //calcula grafico cdf
//    for (x = 0; x < 256; x++)
//    {
//        for (y = x;y >= 0;y--)
//        {
//            cdf[x] += pdf[y];
//        }
//    }
//    
//    
//    for (y = 0;y<height;y++)
//    {
//        for (x = 0;x<width;x++)
//        {
//            pos = y*byteperline + x*channels;
//            dst->data[pos] = cdf[data[pos]] * 255;
//        }
//    }
//    return 1;
//}
//
//bool ApplyHistogramGrayScale(Image *src, Image *dst)
//{
//    unsigned char *data = (unsigned char *)src->data;
//    int width = src->width;
//    int height = src->height;
//    int byteperline = src->width*src->channels;
//    int channels = src->channels;
//    int x, y;
//    long int pos;
//    int contarpixeis[256] = { 0 };
//    float pdf[256];
//    float conta = 0;
//    float max = 0;
//    double temp;
//    float cdf[256] = { 0 };
//    float equalizacao[256] = { 0 };
//    
//    
//    
//    if ((src->width <= 0) || (src->height <= 0) || (src->data == NULL))
//        return 0;
//    if (channels != 1)
//        return 0;
//    
//    //numero pixeis repetidos
//    for (y = 0;y<height;y++)
//    {
//        for (x = 0;x<width;x++)
//        {
//            pos = y*byteperline + x*channels;
//            contarpixeis[(int)data[pos]]++;
//        }
//    }
//    
//    //clacula pdf
//    for (y = 0;y<256;y++)
//    {
//        pdf[y] = (float)contarpixeis[y] / (float)(width*height);
//        conta += pdf[y];
//        
//        if (max<pdf[y])
//            max = pdf[y];
//    }
//    
//    //calcula grafico cdf
//    for (int i =1; i < 256; i++)
//    {
//        cdf[i] = cdf[i - 1] + pdf[i];
//    }
//    
//    for (y = 0;y<height;y++)
//    {
//        for (x = 0;x<width;x++)
//        {
//            pos = y*byteperline + x*channels;
//            dst->data[pos] = cdf[data[pos]] * src->levels;
//        }
//    }
//    return 1;
//}
