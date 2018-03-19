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
#include "Utils.h"
#else
#include "../Entities/Image.h"
#include "../Entities/Blob.h"
#include "../Engine/Labeling.h" //TODO: Márcio Validate
#endif


// Etiquetagem de blobs
// src        : Imagem binaria de entrada
// dst        : Imagem grayscale (ira conter as etiquetas)
// nlabels    : Endereço de memoria de uma variavel, onde ser armazenado o numero de etiquetas encontradas.
// Blob*      : Retorna um array de estruturas de blobs (objectos), com respectivas etiquetas. necessario libertar                    posteriormente esta memoria.
Blob* GetBlobArrayFromImage(Image *src, Image *dst, int *nlabels)
{
    unsigned char *datasrc = (unsigned char *)src->data;
    unsigned char *datadst = (unsigned char *)dst->data;
    int width = src->width;
    int height = src->height;
    int bytesperline = src->bytesperline;
    int channels = src->channels;
    int x, y, a, b;
    long int i, size;
    long int posX, posA, posB, posC, posD;
    int labeltable[256] = { 0 };
    int labelarea[256] = { 0 };
    int label = 1; // Etiqueta inicial.
    int num, tmplabel;
    Blob *blobs; // Apontador para array de blobs (objectos) que sera retornado desta funcao.
    
    // Verificacao de erros
    if ((src->width <= 0) || (src->height <= 0) || (src->data == NULL)) return 0;
    if ((src->width != dst->width) || (src->height != dst->height) || (src->channels != dst->channels)) return NULL;
    if (channels != 1) return NULL;
    
    // Copia dados da imagem binaria para imagem grayscale
    memcpy(datadst, datasrc, bytesperline * height);
    
    // Todos os pixÈis de plano de fundo devem obrigatoriamente ter valor 0
    // Todos os pixÈis de primeiro plano devem obrigatoriamente ter valor 255
    // Ser„o atribuÌdas etiquetas no intervalo [1,254]
    // Este algoritmo esta assim limitado a 255 labels
    for (i = 0, size = bytesperline * height; i<size; i++)
    {
        if (datadst[i] != 0) datadst[i] = 255;
    }
    
    // Limpa os rebordos da imagem binaria
    for (y = 0; y<height; y++)
    {
        datadst[y * bytesperline + 0 * channels] = 0;
        datadst[y * bytesperline + (width - 1) * channels] = 0;
    }
    for (x = 0; x<width; x++)
    {
        datadst[0 * bytesperline + x * channels] = 0;
        datadst[(height - 1) * bytesperline + x * channels] = 0;
    }
    
    // Efectua a etiquetagem
    for (y = 1; y<height - 1; y++)
    {
        for (x = 1; x<width - 1; x++)
        {
            // Kernel:
            // A B C
            // D X
            
            posA = (y - 1) * bytesperline + (x - 1) * channels; // A
            posB = (y - 1) * bytesperline + x * channels; // B
            posC = (y - 1) * bytesperline + (x + 1) * channels; // C
            posD = y * bytesperline + (x - 1) * channels; // D
            posX = y * bytesperline + x * channels; // X
            
            // Se o pixel foi marcado
            if (datadst[posX] != 0)
            {
                if ((datadst[posA] == 0) && (datadst[posB] == 0) && (datadst[posC] == 0) && (datadst[posD] == 0))
                {
                    datadst[posX] = label;
                    labeltable[label] = label;
                    label++;
                }
                else
                {
                    num = 255;
                    
                    // Se A esta marcado
                    if (datadst[posA] != 0) num = labeltable[datadst[posA]];
                    // Se B esta marcado, e È menor que a etiqueta "num"
                    if ((datadst[posB] != 0) && (labeltable[datadst[posB]] < num)) num = labeltable[datadst[posB]];
                    // Se C esta marcado, e È menor que a etiqueta "num"
                    if ((datadst[posC] != 0) && (labeltable[datadst[posC]] < num)) num = labeltable[datadst[posC]];
                    // Se D esta marcado, e È menor que a etiqueta "num"
                    if ((datadst[posD] != 0) && (labeltable[datadst[posD]] < num)) num = labeltable[datadst[posD]];
                    
                    // Atribui a etiqueta ao pixel
                    datadst[posX] = num;
                    labeltable[num] = num;
                    
                    // Actualiza a tabela de etiquetas
                    if (datadst[posA] != 0)
                    {
                        if (labeltable[datadst[posA]] != num)
                        {
                            for (tmplabel = labeltable[datadst[posA]], a = 1; a<label; a++)
                            {
                                if (labeltable[a] == tmplabel)
                                {
                                    labeltable[a] = num;
                                }
                            }
                        }
                    }
                    if (datadst[posB] != 0)
                    {
                        if (labeltable[datadst[posB]] != num)
                        {
                            for (tmplabel = labeltable[datadst[posB]], a = 1; a<label; a++)
                            {
                                if (labeltable[a] == tmplabel)
                                {
                                    labeltable[a] = num;
                                }
                            }
                        }
                    }
                    if (datadst[posC] != 0)
                    {
                        if (labeltable[datadst[posC]] != num)
                        {
                            for (tmplabel = labeltable[datadst[posC]], a = 1; a<label; a++)
                            {
                                if (labeltable[a] == tmplabel)
                                {
                                    labeltable[a] = num;
                                }
                            }
                        }
                    }
                    if (datadst[posD] != 0)
                    {
                        if (labeltable[datadst[posD]] != num)
                        {
                            for (tmplabel = labeltable[datadst[posC]], a = 1; a<label; a++)
                            {
                                if (labeltable[a] == tmplabel)
                                {
                                    labeltable[a] = num;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    // Volta a etiquetar a imagem
    for (y = 1; y<height - 1; y++)
    {
        for (x = 1; x<width - 1; x++)
        {
            posX = y * bytesperline + x * channels; // X
            
            if (datadst[posX] != 0)
            {
                datadst[posX] = labeltable[datadst[posX]];
            }
        }
    }
    
    //printf("\nMax Label = %d\n", label);
    
    // Contagem do n˙mero de blobs
    // Passo 1: Eliminar, da tabela, etiquetas repetidas
    for (a = 1; a<label - 1; a++)
    {
        for (b = a + 1; b<label; b++)
        {
            if (labeltable[a] == labeltable[b]) labeltable[b] = 0;
        }
    }
    // Passo 2: Conta etiquetas e organiza a tabela de etiquetas, para que n„o hajam valores vazios (zero) entre etiquetas
    *nlabels = 0;
    for (a = 1; a<label; a++)
    {
        if (labeltable[a] != 0)
        {
            labeltable[*nlabels] = labeltable[a]; // Organiza tabela de etiquetas
            (*nlabels)++; // Conta etiquetas
        }
    }
    
    // Se n„o ha blobs
    if (*nlabels == 0) return NULL;
    
    // Cria lista de blobs (objectos) e preenche a etiqueta
    blobs = (Blob *)calloc((*nlabels), sizeof(Blob));
    if (blobs != NULL)
    {
        for (a = 0; a<(*nlabels); a++) blobs[a].label = labeltable[a];
    }
    else return NULL;
    
    return blobs;
}


int FillBlobsInfoFromImage(Image *src, Blob *blobs, int nblobs)
{
    unsigned char *data = (unsigned char *)src->data;
    int width = src->width;
    int height = src->height;
    int bytesperline = src->bytesperline;
    int channels = src->channels;
    int x, y, i;
    long int pos;
    int xmin, ymin, xmax, ymax;
    long int sumx, sumy;
    
    // VerificaÁ„o de erros
    if ((src->width <= 0) || (src->height <= 0) || (src->data == NULL)) return 0;
    if (channels != 1) return 0;
    
    // Conta area de cada blob
    for (i = 0; i<nblobs; i++)
    {
        xmin = width - 1;
        ymin = height - 1;
        xmax = 0;
        ymax = 0;
        
        sumx = 0;
        sumy = 0;
        
        blobs[i].area = 0;
        
        for (y = 1; y<height - 1; y++)
        {
            for (x = 1; x<width - 1; x++)
            {
                pos = y * bytesperline + x * channels;
                
                if (data[pos] == blobs[i].label)
                {
                    // ¡rea
                    blobs[i].area++;
                    
                    // Centro de Gravidade
                    sumx += x;
                    sumy += y;
                    
                    // Bounding Box
                    if (xmin > x) xmin = x;
                    if (ymin > y) ymin = y;
                    if (xmax < x) xmax = x;
                    if (ymax < y) ymax = y;
                    
                    // PerÌmetro
                    // Se pelo menos um dos quatro vizinhos n„o pertence ao mesmo label, ent„o È um pixel de contorno
                    if ((data[pos - 1] != blobs[i].label) || (data[pos + 1] != blobs[i].label) || (data[pos - bytesperline] != blobs[i].label) || (data[pos + bytesperline] != blobs[i].label))
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
        //blobs[i].xc = (xmax - xmin) / 2;
        //blobs[i].yc = (ymax - ymin) / 2;
        blobs[i].xc = sumx / Max(blobs[i].area, 1);
        blobs[i].yc = sumy / Max(blobs[i].area, 1);
    }
    
    return 1;
}
