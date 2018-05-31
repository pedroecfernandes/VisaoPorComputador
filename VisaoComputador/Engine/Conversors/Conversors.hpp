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
#include <opencv2/opencv.hpp>

#include <stdbool.h>
#else
#include <stdio.h>
#include "../../Entities/Image.hpp"
#include <opencv2/opencv.hpp>
#include <stdbool.h>
#endif

#endif /* Conversors_h */

bool ConvertRGBToBGR(IplImage *image);
bool ConvertRGBToGrayScaleBasedOnChannel(IplImage *image, IplImage *output, bool RChannel, bool GChannel, bool BChannel);
bool ConvertRBGToHSV(IplImage *image);
bool ConvertBGRToHSV(IplImage *image);
bool ConvertHSVToRGB(IplImage *image);
bool ConvertHSVToBGR(IplImage *image);
