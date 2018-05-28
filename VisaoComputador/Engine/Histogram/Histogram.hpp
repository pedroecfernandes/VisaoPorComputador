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
#include <opencv2/opencv.hpp>

#include <stdbool.h>
#else
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "../../Entities/Image.hpp"
#include <stdbool.h>
#endif

#endif /* Histogram_h */

//bool ApplyHistogramGrayScale(IplImage *src, Image *dst);
//bool GetHistogramGrayScale(IplImage *src, Image *dst);
//bool GetHistogram(IplImage *src, Image *dst);
