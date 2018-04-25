#pragma once
#include "../../VisaoComputador/Entities/Blob.h"
#include "Colors.h"

typedef struct {
	int x;
	int y;
} Position;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                   ESTRUTURA DE UM CONTORNO
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct {
	int label;
	int count;
	Position *positions;
} Contour;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                   ESTRUTURA DE UMA PEÇA
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct {
	Blob blob;
	enum Color color;
	Contour contour;
	//Shape shape;
} Piece;

enum Color GetColorFromHSV(Image *hsvImage, int xc, int yc);
