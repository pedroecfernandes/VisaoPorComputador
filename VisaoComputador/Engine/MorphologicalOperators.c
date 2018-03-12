//
//  MorphologicalOperators.c
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 07/03/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//

#include "MorphologicalOperators.h"
#include "Segmentators.h"

bool ApplyBinaryOpen(Image *input, Image *output, int kernelErode, int kernelDilate)
{
    Image *aux = vc_image_new(input->width, input->height, 1, input->levels);
    
    ApplyBinaryErode(input, aux, kernelErode);
    ApplyBinaryDilate(input, output, kernelDilate);
    
    vc_image_free(aux);
    
    return true;
}

bool ApplyBinaryClose(Image *input, Image *output, int kernelErode, int kernelDilate)
{
    Image *aux = vc_image_new(input->width, input->height, 1, input->levels);
    
    ApplyBinaryDilate(input, aux, kernelDilate);
    ApplyBinaryErode(aux, output, kernelErode);
    
    vc_image_free(aux);
    
    return true;
}
