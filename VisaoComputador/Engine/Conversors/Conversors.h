//
//  Conversors.h
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 26/02/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//

#ifndef Conversors_h
#define Conversors_h

#include <stdio.h>
#include "Image.h"

#endif /* Conversors_h */

#include <stdbool.h>

#ifdef OSX

#else
// TODO: Márcio
#endif

bool ConvertRGBToBGR(Image *image);
bool ConvertRGBToGrayScaleBasedOnChannel(Image *image, Image *output, bool RChannel, bool GChannel, bool BChannel);
bool ConvertRBGToHSV(Image *image);
