#pragma once
#include "../../VisaoComputador/Entities/Blob.h"
#include "Colors.h"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                   ESTRUTURA DE UMA PEÇA
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct {
	Blob blob;
	enum Color color;
	//Shape shape;
} Piece;

enum Color GetColorFromHSV(Image *hsvImage, int xc, int yc);
