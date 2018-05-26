//
//  Outliners.h
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 30/04/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//

#ifndef Outliners_h
#define Outliners_h

#ifdef OSX
#include <stdio.h>
#include <opencv2/opencv.hpp>

#include <stdbool.h>
#else
#include <stdio.h>
#include "../../Entities/Image.h"
#include <stdbool.h>
#endif

#endif /* Outliners_h */

bool ApplyPrewittEdging(IplImage *src, IplImage *dst, float th);
bool ApplySobelEdging(IplImage *src, IplImage *dst, float th);
