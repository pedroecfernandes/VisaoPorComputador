//
//  Filters.h
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 26/02/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//

#ifdef OSX
#include <stdio.h>
#include "Image.h"
#include <stdbool.h>
#else
#include <stdbool.h>
#include "../Entities/Image.h"
#endif

bool ApplyInvertRGB(Image *image);
bool ApplyInvertGrayScale(Image *image);
bool ApplyInvertBinary(Image *image);
