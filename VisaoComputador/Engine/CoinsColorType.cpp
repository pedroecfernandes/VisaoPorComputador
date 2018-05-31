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
#endif



enum CoinType GetColorCoinTypeFromHSV(IplImage *hsvImage)
{
	int bytesperlineHSV = hsvImage->width*hsvImage->nChannels;
	long int posBinary, posHSV;
	double h, s, v;
	int countPixels = 0, i = 0, j = 0;
	int colors[sizeof(COLOR_STRING) / sizeof(int)];
	IplImage *binaryImage = NULL;
	cvCopy(hsvImage, binaryImage, NULL);

	ConvertHSVToBGR(binaryImage);

	int bytesperlineBinary = binaryImage->width*binaryImage->nChannels;

	if ((binaryImage->width <= 0) || (binaryImage->height <= 0) || (binaryImage->imageData == NULL)) return CoinType::UndefinedCoin;
	if (hsvImage->nChannels != 3) return CoinType::UndefinedCoin;

	// initialize array with 0
	for (i = 0; i < (sizeof(colors) / sizeof(int)); i++)
	{
		colors[i] = 0;
	}

	for (i = 0; i < hsvImage->height; i++)
	{
		for (j = 0; j < hsvImage->width; j++)
		{
			posBinary = i * bytesperlineBinary + j * binaryImage->nChannels;

			if (binaryImage->imageData[posBinary] == 255)
			{
				posHSV = i * bytesperlineHSV + j * hsvImage->nChannels;

				h = ((double)hsvImage->imageData[posHSV] * 360.0) / 255.0;
				s = ((double)hsvImage->imageData[posHSV] * 100.0) / 255.0;
				v = ((double)hsvImage->imageData[posHSV] * 100.0) / 255.0;

				if((h >= 20 && h <= 40) && (s >= 35 && s <= 75) && (v >= 20 && v <= 40))
				{
					colors[Bronze]++;
				}
				else if ((h >= 40 && h <= 60) && (s >= 30 && s <= 65) && (v >= 35 && v <= 50))
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

				countPixels++;
			}
		}
	}

	if ((colors[Bronze] / countPixels) > 0.85)
	{
		return CoinType::DarkCoin;
	}
	else if ((colors[Gold] / countPixels) > 0.85)
	{
		return CoinType::GoldCoin;
	}
	else if (((colors[Gold] / countPixels) > 0.65 && (colors[Silver] / countPixels) > 0.10) || ((colors[Silver] / countPixels) > 0.65 && (colors[Gold] / countPixels) > 0.10))
	{
		return CoinType::MixedCoin;
	}

	return CoinType::UndefinedCoin;
}
