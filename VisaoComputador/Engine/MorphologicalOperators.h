//
//  MorphologicalOperators.h
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 07/03/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//

#include <stdio.h>
#include "Image.h"
#include <stdbool.h>


bool ApplyBinaryOpen(Image *input, Image *dst, int kernelErode, int kernelDilate);
bool ApplyBinaryClose(Image *input, Image *output, int kernelErodeinput, int kernelDilate);;
