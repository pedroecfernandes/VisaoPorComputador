//
//  Segmentators.h
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 07/03/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//

#include <stdio.h>
#include "Image.h"
#include <stdbool.h>

bool ApplyGrayScaleBinaryThreshold(Image *image, int threshold);
bool ApplyGrayScaleBinaryMidpoint(Image *input, Image *output, int kernel);
bool ApplyBinaryDilate(Image *input, Image *output, int kernel);
bool ApplyBinaryErode(Image *input, Image *output, int kernel);
