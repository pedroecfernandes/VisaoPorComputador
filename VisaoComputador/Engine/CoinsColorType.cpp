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
	long int posBinary, posHSV;
	double h, s, v;
	double minH = 255, maxH = 0, minS = 255, maxS = 0, minV = 255, maxV = 0;
	int countPixels = 0, i = 0, j = 0;
	int colors[4];

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
			posBinary = i * binaryImage->widthStep + j;

			if ((double)binaryImage->imageData[posBinary] == -1)
			{
				h = ((double)hsvImage->imageData[i * hsvImage->widthStep + (j * hsvImage->nChannels)] * 360.0) / 255.0;
				s = ((double)hsvImage->imageData[i * hsvImage->widthStep + ((j * hsvImage->nChannels) + 1)] * 100.0) / 255.0;
				v = ((double)hsvImage->imageData[i * hsvImage->widthStep + ((j * hsvImage->nChannels) + 2)] * 100.0) / 255.0;

				if (h >= 20 && h < 40)
				{
					colors[Bronze]++;
				}
				else if (h >= 40 && h <= 70)
				{
					colors[Gold]++;
				}
				else if ((s >= 0 && s <= 25) && (v >= 15 && v <= 65))
				{
					colors[Silver]++;
				}
				else
				{
					colors[Undefined]++;
				}

				countPixels++;
			}
		}
	}

	if (countPixels != 0)
	{
		if (((double)colors[Bronze] / (double)countPixels) > 0.85)
		{
			return CoinType::DarkCoin;
		}
		if (((double)colors[Gold] / (double)countPixels) > 0.85)
		{
			return CoinType::GoldCoin;
		}
		if ((((double)colors[Gold] / (double)countPixels) > 0.50 && ((double)colors[Silver] / (double)countPixels) > 0.15) || (((double)colors[Silver] / (double)countPixels) > 0.50 && ((double)colors[Gold] / (double)countPixels) > 0.15))
		{
			return CoinType::MixedCoin;
		}
	}
    
	return CoinType::UndefinedCoin;
}
