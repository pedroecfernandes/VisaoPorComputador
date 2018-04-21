#include "../../VisaoComputador/Entities/Image.h"
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include "../../VisaoComputador/Engine/Colors.h"


enum Color GetColorFromHSV(Image *image, int xc, int yx)
{
	int bytesperline = image->width*image->channels;
	long int pos;
	int h;

	if ((image->width <= 0) || (image->height <= 0) || (image->data == NULL)) return false;
	if (image->channels != 3) return -1;

	// get position from center of mass
	pos = yx * bytesperline + xc * image->channels;

	h = (float)image->data[pos];

	printf("h: %d", h);

	if (h <= 12 || h >= 338)
		return Red;
	if (h >= 13 && h <= 41)
		return Orange;
	if (h >= 42 && h <= 69)
		return Yellow;
	if (h >= 70 && h <= 153)
		return Green;
	if (h >= 154 && h <= 203)
		return Cyan;
	if (h >= 204 && h <= 251)
		return Blue;
	if (h >= 252 && h <= 299)
		return Purple;
	if (h >= 300 && h <= 337)
		return Pink;

	return -1;
}
