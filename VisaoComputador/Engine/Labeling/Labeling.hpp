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
#include "Blob.hpp"
#include "Image.hpp"
#include <stdbool.h>
#else
#include "../../Entities/Image.h"
#include "../../Entities/Blob.h"
#include <stdbool.h>
#endif


Blob* GetBlobArrayFromImage(Image *src, Image *dst, int *nlabels);
int FillBlobsInfoFromImage(Image *src, Blob *blobs, int nblobs);
bool ExtractImageFromBlob(Blob blob, Image *blobSrcImage, Image *blobDstImage);
bool CleanBinaryImageBorders(Image *blobImage);
void HighlightBlobInRGBImage(Image *image, Blob *blob, int hR, int hG, int hB);
