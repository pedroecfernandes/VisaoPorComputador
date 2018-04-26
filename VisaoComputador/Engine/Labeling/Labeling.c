//
//  Labeling.c
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 19/03/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//

#ifdef OSX
#include "Blob.h"
#include "Image.h"
#include "Labeling.h"
#include <stdbool.h>
#include "Utils.h"
#else
#include "../../Entities/Image.h"
#include "../../Entities/Blob.h"
#include "../../Engine/Labeling/Labeling.h"
#include "../Pieces.h"
#include "../../Engine/Utils.h"
#include <stdlib.h>
#include <string.h>
#endif

<<<<<<< HEAD
=======
bool CleanBinaryImageBorders(Image *blobImage)
{
    int pos = 0;
    
    for (int y = 0; y < blobImage->height; y++)
    {
        for (int x = 0; x < blobImage->width; x++)
        {
            pos = y * blobImage->bytesperline + x * blobImage->channels;
            
            if (blobImage->data[pos] == 0)
                blobImage->data[pos] = 1;
            else
                break;
        }
    }
    
    for (int y = 0; y < blobImage->height; y++)
    {
        for (int x = blobImage->width - 1; x > 0; x--)
        {
            pos = y * blobImage->bytesperline + x * blobImage->channels;
            
            if (blobImage->data[pos] == 0)
                blobImage->data[pos] = 1;
            else
                break;
        }
    }
    
    return true;
}

// Creates an highlighted box arround the blob
void HighlightBlobInRGBImage(Image *image, Blob *blob, int hR, int hG, int hB)
{
    int pos = 0;
    
    for (int y = blob->y; y < blob->height + blob->y; y++)
    {
        pos = y * image->bytesperline + blob->x * image->channels;
    
        image->data[pos] = hR;
        image->data[pos + 1] = hG;
        image->data[pos + 2] = hB;
        
        pos = y * image->bytesperline + (blob->x + blob->width - 1) * image->channels;
        image->data[pos] = hR;
        image->data[pos + 1] = hG;
        image->data[pos + 2] = hB;
    }
    
    for (int x = blob->x; x < blob->width + blob->x; x++)
    {
        pos = blob->y * image->bytesperline + x * image->channels;
        
        image->data[pos] = hR;
        image->data[pos + 1] = hG;
        image->data[pos + 2] = hB;
        
        pos = (blob->y + blob->height -1 ) * image->bytesperline + x * image->channels;
        
        image->data[pos] = hR;
        image->data[pos + 1] = hG;
        image->data[pos + 2] = hB;
    }
}

//  Usage:
//      Image *blobImage = vc_image_new(blobs[i].width, blobs[i].height, image->channels, image->levels);
//      ExtractImageFromBlob(blobs[i], image, blobImage);
//      vc_image_free(blobImage);
bool ExtractImageFromBlob(Blob blob, Image *blobSrcImage, Image *blobDstImage)
{    
    int posblobOnSrcImage = 0;
    int posDiceImage = 0;
    int blobDiceImageX = 0, blobDiceImageY = 0;
    
    for (int x = blob.x; x < blob.x + blob.width; x++)
    {
        blobDiceImageY = 0;
        
        for (int y = blob.y; y < blob.y + blob.height; y++)
        {
            posblobOnSrcImage = y * blobSrcImage->bytesperline + x * blobSrcImage->channels;
            posDiceImage = blobDiceImageY * blobDstImage->bytesperline + blobDiceImageX * blobDstImage->channels;
            
            // Copy color value
            blobDstImage->data[posDiceImage] = blobSrcImage->data[posblobOnSrcImage];
            
            // RGB Treatment
            if (blobSrcImage->channels == 3)
            {
                blobDstImage->data[posDiceImage + 1] = blobSrcImage->data[posblobOnSrcImage + 1];
                blobDstImage->data[posDiceImage + 2] = blobSrcImage->data[posblobOnSrcImage + 2];
            }
            
            blobDiceImageY++;
        }
        
        blobDiceImageX++;
    }
    
    return true;
}
>>>>>>> 995d97458ee33e719337384e750cdc876242d693

// Etiquetagem de blobs
// src        : Imagem bin·ria
// dst        : Imagem grayscale (ir· conter as etiquetas)
// nlabels    : EndereÁo de memÛria de uma vari·vel inteira. Recebe o n˙mero de etiquetas encontradas.
// Blob*      : Retorna lista de estruturas de blobs (objectos), com respectivas etiquetas. … necess·rio libertar posteriormente esta memÛria.
Blob* GetBlobArrayFromImage(Image *src, Image *dst, int *nlabels)
{
    unsigned char *datasrc = (unsigned char *) src->data;
    unsigned char *datadst = (unsigned char *) dst->data;
    int width = src->width;
    int height = src->height;
    int bytesperline = src->bytesperline;
    int channels = src->channels;
    int x, y, a, b;
    long int i, size;
    long int posX, posA, posB, posC, posD;
    int labeltable[256] = {0};
    int labelarea[256] = {0};
    int label = 1; // Etiqueta inicial.
    int num;
    Blob *blobs; // Apontador para lista de blobs (objectos) que ser· retornada desta funÁ„o.
    
    // VerificaÁ„o de erros
    if((src->width <= 0) || (src->height <= 0) || (src->data == NULL)) return 0;
    if((src->width != dst->width) || (src->height != dst->height) || (src->channels != dst->channels)) return NULL;
    if(channels != 1) return NULL;
    
    // Copia dados da imagem bin·ria para imagem grayscale
    memcpy(datadst, datasrc, bytesperline * height);
    
    // Todos os pixÈis de plano de fundo devem obrigatÛriamente ter valor 0
    // Todos os pixÈis de primeiro plano devem obrigatÛriamente ter valor 255
    // Ser„o atribuÌdas etiquetas no intervalo [1,254]
    // Este algoritmo est· assim limitado a 254 labels
    for(i=0, size = bytesperline * height; i<size; i++)
    {
        if(datadst[i] != 0) datadst[i] = 255;
    }
    
    // Limpa os rebordos da imagem bin·ria
    for(y=0; y<height; y++)
    {
        datadst[y * bytesperline + 0 * channels] = 0;
        datadst[y * bytesperline + (width-1) * channels] = 0;
    }
    for(x=0; x<width; x++)
    {
        datadst[0 * bytesperline + x * channels] = 0;
        datadst[(height-1) * bytesperline + x * channels] = 0;
    }
    
    // Efectua a etiquetagem
    for(y=1; y<height-1; y++)
    {
        for(x=1; x<width-1; x++)
        {
            // Kernel:
            // A B C
            // D X
            
            posA = (y-1) * bytesperline + (x-1) * channels; // A
            posB = (y-1) * bytesperline + x * channels; // B
            posC = (y-1) * bytesperline + (x+1) * channels; // C
            posD = y * bytesperline + (x-1) * channels; // D
            posX = y * bytesperline + x * channels; // X
            
            // Se o pixel foi marcado
            if(datadst[posX] != 0)
            {
                if((datadst[posA] == 0) && (datadst[posB] == 0) && (datadst[posC] == 0) && (datadst[posD] == 0))
                {
                    datadst[posX] = label;
                    labeltable[label] = label;
                    label++;
                }
                else
                {
                    num = 255;
                    
                    // Se A est· marcado, j· tem etiqueta (j· n„o È 255), e È menor que a etiqueta "num"
                    if((datadst[posA] != 0) && (datadst[posA] != 255) && (datadst[posA] < num))
                    {
                        num = datadst[posA];
                    }
                    // Se B est· marcado, j· tem etiqueta (j· n„o È 255), e È menor que a etiqueta "num"
                    if((datadst[posB] != 0) && (datadst[posB] != 255) && (datadst[posB] < num))
                    {
                        num = datadst[posB];
                    }
                    // Se C est· marcado, j· tem etiqueta (j· n„o È 255), e È menor que a etiqueta "num"
                    if((datadst[posC] != 0) && (datadst[posC] != 255) && (datadst[posC] < num))
                    {
                        num = datadst[posC];
                    }
                    // Se D est· marcado, j· tem etiqueta (j· n„o È 255), e È menor que a etiqueta "num"
                    if((datadst[posD] != 0) && (datadst[posD] != 255) && (datadst[posD] < num))
                    {
                        num = datadst[posD];
                    }
                    
                    // Actualiza a tabela de etiquetas
                    if((datadst[posA] != 0) && (datadst[posA] != 255))
                    {
                        if(labeltable[datadst[posA]] != labeltable[num])
                        {
                            for(a=1; a<label; a++)
                            {
                                if(labeltable[a] == labeltable[datadst[posA]])
                                {
                                    labeltable[a] = labeltable[num];
                                }
                            }
                        }
                    }
                    if((datadst[posB] != 0) && (datadst[posB] != 255))
                    {
                        if(labeltable[datadst[posB]] != labeltable[num])
                        {
                            for(a=1; a<label; a++)
                            {
                                if(labeltable[a] == labeltable[datadst[posB]])
                                {
                                    labeltable[a] = labeltable[num];
                                }
                            }
                        }
                    }
                    if((datadst[posC] != 0) && (datadst[posC] != 255))
                    {
                        if(labeltable[datadst[posC]] != labeltable[num])
                        {
                            for(a=1; a<label; a++)
                            {
                                if(labeltable[a] == labeltable[datadst[posC]])
                                {
                                    labeltable[a] = labeltable[num];
                                }
                            }
                        }
                    }
                    if((datadst[posD] != 0) && (datadst[posD] != 255))
                    {
                        if(labeltable[datadst[posD]] != labeltable[num])
                        {
                            for(a=1; a<label; a++)
                            {
                                if(labeltable[a] == labeltable[datadst[posD]])
                                {
                                    labeltable[a] = labeltable[num];
                                }
                            }
                        }
                    }
                    labeltable[datadst[posX]] = num;
                    
                    // Atribui a etiqueta ao pixel
                    datadst[posX] = num;
                }
            }
        }
    }
    
    // Volta a etiquetar a imagem
    for(y=1; y<height-1; y++)
    {
        for(x=1; x<width-1; x++)
        {
            posX = y * bytesperline + x * channels; // X
            
            if(datadst[posX] != 0)
            {
                datadst[posX] = labeltable[datadst[posX]];
            }
        }
    }
    
    // Contagem do n˙mero de blobs
    // Passo 1: Eliminar, da tabela, etiquetas repetidas
    for(a=1; a<label-1; a++)
    {
        for(b=a+1; b<label; b++)
        {
            if(labeltable[a] == labeltable[b]) labeltable[b] = 0;
        }
    }
    // Passo 2: Conta etiquetas e organiza a tabela de etiquetas, para que n„o hajam valores vazios (zero) entre etiquetas
    *nlabels = 0;
    for(a=1; a<label; a++)
    {
        if(labeltable[a] != 0)
        {
            labeltable[*nlabels] = labeltable[a]; // Organiza tabela de etiquetas
            (*nlabels)++; // Conta etiquetas
        }
    }
    
    // Se n„o h· blobs
    if(*nlabels == 0) return NULL;
    
    // Cria lista de blobs (objectos) e preenche a etiqueta
    blobs = (Blob *) calloc((*nlabels), sizeof(Blob));
    if(blobs != NULL)
    {
        for(a=0; a<(*nlabels); a++) blobs[a].label = labeltable[a];
    }
    else return NULL;
    
    return blobs;
}


int FillBlobsInfoFromImage(Image *src, Blob *blobs, int nblobs)
{
    unsigned char *data = (unsigned char *) src->data;
    int width = src->width;
    int height = src->height;
    int bytesperline = src->bytesperline;
    int channels = src->channels;
    int x, y, i;
    long int pos;
    int xmin, ymin, xmax, ymax;
    long int sumx, sumy;
    
    // VerificaÁ„o de erros
    if((src->width <= 0) || (src->height <= 0) || (src->data == NULL)) return 0;
    if(channels != 1) return 0;
    
    // Conta ·rea de cada blob
    for(i=0; i<nblobs; i++)
    {
        xmin = width - 1;
        ymin = height - 1;
        xmax = 0;
        ymax = 0;
        
        sumx = 0;
        sumy = 0;
        
        blobs[i].area = 0;
        
        for(y=1; y<height-1; y++)
        {
            for(x=1; x<width-1; x++)
            {
                pos = y * bytesperline + x * channels;
                
                if(data[pos] == blobs[i].label)
                {
                    // ¡rea
                    blobs[i].area++;
                    
                    // Centro de Gravidade
                    sumx += x;
                    sumy += y;
                    
                    // Bounding Box
                    if(xmin > x) xmin = x;
                    if(ymin > y) ymin = y;
                    if(xmax < x) xmax = x;
                    if(ymax < y) ymax = y;
                    
                    // PerÌmetro
                    // Se pelo menos um dos quatro vizinhos n„o pertence ao mesmo label, ent„o È um pixel de contorno
                    if((data[pos - 1] != blobs[i].label) || (data[pos + 1] != blobs[i].label) || (data[pos - bytesperline] != blobs[i].label) || (data[pos + bytesperline] != blobs[i].label))
                    {
                        blobs[i].perimeter++;

                    }
                }
            }
        }
        
        // Bounding Box
        blobs[i].x = xmin;
        blobs[i].y = ymin;
        blobs[i].width = (xmax - xmin) + 1;
        blobs[i].height = (ymax - ymin) + 1;
        
        // Centro de Gravidade
        blobs[i].xc = sumx / (blobs[i].area > 1 ? blobs[i].area : 1);
        blobs[i].yc = sumy / (blobs[i].area > 1 ? blobs[i].area : 1);
    }
    
    return 1;
}

// Creates an highlighted box arround the blob
void HighlightBlobInRGBImage(Image *image, Blob *blob, int hR, int hG, int hB)
{
	int pos = 0;

	for (int y = blob->y; y < blob->height + blob->y; y++)
	{
		pos = y * image->bytesperline + blob->x * image->channels;

		image->data[pos] = hR;
		image->data[pos + 1] = hG;
		image->data[pos + 2] = hB;
	}

	for (int x = blob->x; x < blob->width + blob->x; x++)
	{
		pos = blob->y * image->bytesperline + x * image->channels;

		image->data[pos] = hR;
		image->data[pos + 1] = hG;
		image->data[pos + 2] = hB;
	}

	for (int y = blob->height + blob->y; y > blob->y; y--)
	{
		pos = y * image->bytesperline + (blob->width + blob->x) * image->channels;

		image->data[pos] = hR;
		image->data[pos + 1] = hG;
		image->data[pos + 2] = hB;
	}

	for (int x = blob->width + blob->x; x > blob->x; x--)
	{
		pos = (blob->height + blob->y) * image->bytesperline + x * image->channels;

		image->data[pos] = hR;
		image->data[pos + 1] = hG;
		image->data[pos + 2] = hB;
	}
}

// Creates an highlighted box arround the blob
void HighlightMassCenterInRGBImage(Image *image, int xc, int yc, int radius, int hR, int hG, int hB)
{
	int pos = 0;

	for (int y = yc - radius; y < yc + radius; y++)
	{
		pos = y * image->bytesperline + (xc - radius) * image->channels;

		image->data[pos] = hR;
		image->data[pos + 1] = hG;
		image->data[pos + 2] = hB;
	}

	for (int x = xc - radius; x < xc + radius; x++)
	{
		pos = (yc + radius) * image->bytesperline + x * image->channels;

		image->data[pos] = hR;
		image->data[pos + 1] = hG;
		image->data[pos + 2] = hB;
	}

	for (int y = yc + radius; y > yc - radius; y--)
	{
		pos = y * image->bytesperline + (xc + radius) * image->channels;

		image->data[pos] = hR;
		image->data[pos + 1] = hG;
		image->data[pos + 2] = hB;
	}

	for (int x = xc + radius; x > xc - radius; x--)
	{
		pos = (yc - radius) * image->bytesperline + x * image->channels;

		image->data[pos] = hR;
		image->data[pos + 1] = hG;
		image->data[pos + 2] = hB;
	}
}

