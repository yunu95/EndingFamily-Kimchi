#include "BoxImage.h"
void BoxImage::SetBoxImage(int width, int height, char outline)
{
	imageMatrix = vector<vector<char>>(height, vector<char>(width, ' '));
	this->width = width;
	this->height = height;
	// do things
	int w = width;
	int h = height;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			imageMatrix[i][j] = NULL;
		}
	}

	// ���� ù°��, �������� ť��
	for (int i = 0; i < w; i++)
	{
		imageMatrix[0][i] = outline;
		imageMatrix[h - 1][i] = outline;
	}

	// ���� �� ť��
	for (int j = 1; j < h - 1; j++)
	{
		for (int i = 1; i < w - 1; i++)
		{
			imageMatrix[j][0] = outline;
			imageMatrix[j][i] = ' ';
			imageMatrix[j][w - 1] = outline;
		}
	}
}
