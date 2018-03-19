//
//  Labeling.h
//  VisaoComputador
//
//  Created by Pedro C. Fernandes on 19/03/18.
//  Copyright © 2018 Pedro C. Fernandes. All rights reserved.
//

#ifndef Labeling_h
#define Labeling_h

#include <stdio.h>

#endif /* Labeling_h */


#ifdef OSX
#include "Blob.h"
#include "Image.h"
#else
#include "../../Entities/Image.h"
#include "../../Entities/Blob.h"
#endif


Blob* GetBlobArrayFromImage(Image *src, Image *dst, int *nlabels);
int FillBlobsInfoFromImage(Image *src, Blob *blobs, int nblobs);
