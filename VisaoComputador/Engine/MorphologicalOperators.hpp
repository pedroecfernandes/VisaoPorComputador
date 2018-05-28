//
//  MorphologicalOperators.h
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
#include "../Entities/Image.hpp"
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <stdbool.h>
#endif

//bool ApplyBinaryOpen(Image *input, Image *dst, int kernelErode, int kernelDilate);
//bool ApplyBinaryClose(Image *input, Image *output, int kernelErodeinput, int kernelDilate);
