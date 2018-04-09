//
//  Conversors.h
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 26/02/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//

#ifndef Conversors_h
#define Conversors_h

#ifdef OSX
#include <stdio.h>
#include "Image.h"

#include <stdbool.h>
#else
#include <stdio.h>
#include "../../Entities/Image.h"
#include <stdbool.h>
#endif

#endif /* Conversors_h */

bool ConvertRGBToBGR(Image *image);
bool ConvertRGBToGrayScaleBasedOnChannel(Image *image, Image *output, bool RChannel, bool GChannel, bool BChannel);
bool ConvertRGBToGrayScale(Image *image, Image *output);
bool ConvertRBGToHSV(Image *image);
bool ConvertHSVToBinary(Image *image);
