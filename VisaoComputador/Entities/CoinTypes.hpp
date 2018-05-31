#ifdef OSX
#include "Blob.hpp"
#include <stdbool.h>
#else
#include <opencv2/opencv.hpp>
#endif


enum CoinType {
	DarkCoin,
	GoldCoin,
	MixedCoin,
	UndefinedCoin
};

enum CoinType GetColorCoinTypeFromHSV(IplImage *hsvImage);
