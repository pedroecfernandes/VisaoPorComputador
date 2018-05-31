
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                   ESTRUTURA DE UMA COR
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
enum Color {
	Gold,
	Bronze,
	Silver,
	Undefined
};

static const char *COLOR_STRING[] = {
	"Red", "Orange/Beige", "Yellow", "Green",
	"Blue", "Cyan", "Purple", "Pink"
};


#ifdef OSX
#include "Blob.hpp"
#include <stdbool.h>
#else
#include <opencv2/opencv.hpp>
#endif

enum Color GetColorFromHSV(IplImage *image, int xc, int yc);
