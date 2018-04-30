//
//  Histogram.h
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 30/04/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//

#ifndef Histogram_h
#define Histogram_h

#ifdef OSX
#include <stdio.h>
#include "Image.h"

#include <stdbool.h>
#else
#include <stdio.h>
#include "../../Entities/Image.h"
#include <stdbool.h>
#endif

#endif /* Histogram_h */

bool ApplyHistogramGrayScale(Image *src, Image *dst);
bool GetHistogramGrayScale(Image *src, Image *dst);
bool GetHistogram(Image *src, Image *dst);
