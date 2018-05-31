#ifdef OSX
#include "Blob.hpp"
#include <stdbool.h>
#else
#include <stdbool.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#endif
#include "../Entities/Colors.hpp"


enum Color GetColorFromHSV(IplImage *image, int xc, int yc)
{
	int bytesperline = image->width*image->nChannels;
	long int pos;
	double h;
	int s, v, count = 0, i = 0, j = 0;
	float sumHue = 0;
	int colors[sizeof(COLOR_STRING) / sizeof(int)];
	enum Color color = Red;

	if ((image->width <= 0) || (image->height <= 0) || (image->imageData == NULL)) return false;
	if (image->nChannels != 3) return -1;

	// initialize array with 0
	for (i = 0; i < (sizeof(colors) / sizeof(int)); i++)
	{
		colors[i] = 0;
	}

	for (i = yc - 10; i < yc + 10; i++)
	{
		for (j = xc - 10; j < xc + 10; j++)
		{
			pos = i * bytesperline + j * image->nChannels;

			if ((double)image->imageData[pos + 2] > 0.0f)
			{
				h = ((double)image->imageData[pos] * 360.0) / 255.0;

				if (h <= 12 || h >= 338)
					colors[Red]++;
				else if (h >= 13 && h < 42)
					colors[Orange]++;
				else if (h >= 42 && h < 70)
					colors[Yellow]++;
				else if (h >= 70 && h < 154)
					colors[Green]++;
				else if (h >= 154 && h < 204)
					colors[Cyan]++;
				else if (h >= 204 && h < 252)
					colors[Blue]++;
				else if (h >= 252 && h < 300)
					colors[Purple]++;
				else if (h >= 300 && h < 338)
					colors[Pink]++;
			}
		}
	}

	// Get color with most cases
	for (i = 1; i < (sizeof(colors) / sizeof(int)); i++)
	{
		// Change < to > if you want to find the smallest element
		if (colors[color] < colors[i])
		{
			color = i;
		}
	}

	return color;
}
