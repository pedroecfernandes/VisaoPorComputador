//
//  Segmentators.h
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 07/03/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//



#ifdef OSX
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <stdbool.h>
#else
#include <stdio.h>
#include "../Entities/Image.hpp"
#include <opencv2/opencv.hpp>
#include <stdbool.h>
#endif

bool ApplyGrayScaleToBinary(IplImage *image, int threshold);
bool ApplyGrayScaleBinaryMidpoint(IplImage *input, IplImage *output, int kernel);
bool ApplyBinaryDilate(IplImage *input, IplImage *output, int kernel);
bool ApplyBinaryErode(IplImage *input, IplImage *output, int kernel);
