//
//  Image.h
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 26/02/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//

#ifndef IVC_h
#define IVC_h


#endif /* IVC_h */

#pragma once
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                   ESTRUTURA DE UMA IMAGEM
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct {
    unsigned char *data;
    int width, height;
    int channels;            // Bin·rio/Cinzentos=1; RGB=3
    int levels;                // Bin·rio=1; Cinzentos [1,255]; RGB [1,255]
    int bytesperline;        // width * channels
} Image;
