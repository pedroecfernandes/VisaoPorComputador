//
//  Segmentators.h
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 07/03/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//



#ifdef OSX
#include <stdio.h>
#include "Image.h"
#include <stdbool.h>
#else
#include <stdio.h>
#include "../Entities/Image.h"
#include <stdbool.h>
#endif

bool ApplyGrayScaleBinaryThreshold(Image *image, int threshold);
bool ApplyGrayScaleBinaryMidpoint(Image *input, Image *output, int kernel);
bool ApplyBinaryDilate(Image *input, Image *output, int kernel);
bool ApplyBinaryErode(Image *input, Image *output, int kernel);
