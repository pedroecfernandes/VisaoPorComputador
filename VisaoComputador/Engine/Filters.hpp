//
//  Filters.h
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 26/02/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//

#ifdef OSX
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <stdbool.h>
#else
#include <stdbool.h>
#include "../Entities/Image.hpp"
#include <opencv2/opencv.hpp>
#endif

bool ApplyInvertRGB(IplImage *image);
bool ApplyInvertGrayScale(IplImage *image);
bool ApplyInvertBinary(IplImage *image);
