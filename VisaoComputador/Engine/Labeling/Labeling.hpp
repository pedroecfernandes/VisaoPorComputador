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
#include <stdbool.h>
#else
#include "../../Entities/Image.hpp"
#include "../../Entities/Blob.hpp"
#include <stdbool.h>
#endif


Blob* GetBlobArrayFromImage(IplImage *src, IplImage *dst, int *nlabels);
int FillBlobsInfoFromImage(IplImage *src, Blob *blobs, int nblobs);
bool ExtractImageFromBlob(Blob blob, IplImage *blobSrcImage, IplImage *blobDstImage);
bool CleanBinaryImageBorders(IplImage *blobImage);
void HighlightBlobInRGBImage(IplImage *image, Blob *blob, int hR, int hG, int hB);
