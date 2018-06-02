#ifdef OSX
#include "Blob.hpp"
#include <stdbool.h>
#include <opencv2/opencv.hpp>
#include "Colors.hpp"
#include "CoinTypes.hpp"
#include "Conversors/Conversors.hpp"
#else
#include <stdbool.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "../Entities/Colors.hpp"
#include "../Entities/CoinTypes.hpp"
#include "Conversors/Conversors.hpp"
#include "../Entities/Blob.hpp"
#endif



enum CoinType GetColorCoinTypeFromHSV(IplImage *hsvImage, IplImage *binaryImage, Blob *blob)
{
	int bytesperlineHSV = hsvImage->width*hsvImage->nChannels;
	long int posBinary, posHSV;
	double h, s, v;
	double minH = 255, maxH = 0, minS = 255, maxS = 0, minV = 255, maxV = 0;
	int countPixels = 0, i = 0, j = 0;
	int colors[4];
	int bytesperlineBinary = binaryImage->width*binaryImage->nChannels;

	if ((binaryImage->width <= 0) || (binaryImage->height <= 0) || (binaryImage->imageData == NULL)) return CoinType::UndefinedCoin;
	if (hsvImage->nChannels != 3) return CoinType::UndefinedCoin;

	// initialize array with 0
	for (i = 0; i < 4; i++)
	{
		colors[i] = 0;
	}

	for (i = blob->y; i < blob->y + blob->height; i++)
	{
		for (j = blob->x; j < blob->x + blob->width; j++)
		{
			posBinary = i * bytesperlineBinary + j * binaryImage->nChannels;

			if ((double)binaryImage->imageData[posBinary] == -1)
			{
				posHSV = i * bytesperlineHSV + j * hsvImage->nChannels;

				h = ((double)hsvImage->imageData[posHSV] * 360.0) / 255.0;
				s = ((double)hsvImage->imageData[posHSV+1] * 100.0) / 255.0;
				v = ((double)hsvImage->imageData[posHSV+2] * 100.0) / 255.0;

				if(h >= 20 && h <= 45)
				{
					colors[Bronze]++;
				}
				else if ((h >= 45 && h <= 70))
				{
					colors[Gold]++;
				}
				else if ((h >= 40 && h <= 125) && (s >= 0 && s <= 25) && (v >= 10 && v <= 40))
				{
					colors[Silver]++;
				}
				else
				{
					colors[Undefined]++;
				}

				if (h > maxH)
					maxH = h;
				if (h < minH)
					minH = h;
				if (s > maxS)
					maxS = s;
				if (s < minS)
					minS = s;
				if (v > maxV)
					maxV = v;
				if (v < minV)
					minV = v;

				countPixels++;
			}
		}
	}

	/*printf("maxH: %f  | minH: %f\n", maxH, minH);
	printf("maxS: %f  | minS: %f\n", maxS, minS);
	printf("maxV: %f  | minV: %f\n\n", maxV, minV);*/

	if (countPixels != 0)
	{
		if (((double)colors[Bronze] / (double)countPixels) > 0.85)
		{
			return CoinType::DarkCoin;
		}
		else if (((double)colors[Gold] / (double)countPixels) > 0.85)
		{
			return CoinType::GoldCoin;
		}
		else if ((((double)colors[Gold] / (double)countPixels) > 0.35 && ((double)colors[Silver] / (double)countPixels) > 0.20) || (((double)colors[Silver] / (double)countPixels) > 0.35 && ((double)colors[Gold] / (double)countPixels) > 0.20))
		{
			return CoinType::MixedCoin;
		}
	}

	return CoinType::UndefinedCoin;
}
