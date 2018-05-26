//
//  Blob.h
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 19/03/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//

#ifndef Blob_h
#define Blob_h


#endif /* Blob_h */

#pragma once
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                   ESTRUTURA DE UM OBJETO/BLOB
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct {
    int x, y, width, height;    // Caixa Delimitadora (Bounding Box)
    int area;                    // ¡rea
    int xc, yc;                    // Centro-de-massa
    int perimeter;                // PerÌmetro
    int label;                    // Etiqueta
} Blob;
