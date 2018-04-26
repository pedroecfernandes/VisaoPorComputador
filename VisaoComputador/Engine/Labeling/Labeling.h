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
#include "../Pieces.h"

#endif /* Labeling_h */


#ifdef OSX
#include "Blob.h"
#include "Image.h"
#include <stdbool.h>
#else
#include "../../Entities/Image.h"
#include "../../Entities/Blob.h"
#include <stdbool.h>
#endif


Blob* GetBlobArrayFromImage(Image *src, Image *dst, int *nlabels);
int FillBlobsInfoFromImage(Image *src, Blob *blobs, int nblobs);
<<<<<<< HEAD
void HighlightBlobInRGBImage(Image *image, Blob *blob, int hR, int hG, int hB);
<<<<<<< HEAD
void HighlightMassCenterInRGBImage(Image *image, int xc, int yc, int radius, int hR, int hG, int hB);
=======
void HighlightMassCenterInRGBImage(Image *image, int xc, int yc, int radius, int hR, int hG, int hB);
Contour* GetContourBlobsFromImage(Image *src, Blob *blobs, int nblobs);
=======
bool ExtractImageFromBlob(Blob blob, Image *blobSrcImage, Image *blobDstImage);
bool CleanBinaryImageBorders(Image *blobImage);
void HighlightBlobInRGBImage(Image *image, Blob *blob, int hR, int hG, int hB);
>>>>>>> 995d97458ee33e719337384e750cdc876242d693
>>>>>>> f62a59b1b3bb12e7486e2175565489ca6290717a
