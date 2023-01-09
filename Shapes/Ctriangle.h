#pragma once

#include "shape.h"

#include <fstream>

class Ctriangle : public shape
{
private:
	Point Corner1;
	Point Corner2;
	Point Corner3;
	Point Center;
public:
	Ctriangle(Point, Point, Point, GfxInfo shapeGfxInfo);
	virtual ~Ctriangle();
	virtual void Save(ofstream& OutFile);
	void Load(ifstream& Infile);
	virtual shape* copy();
	virtual void Draw(GUI* pUI) const;
	virtual shape* duplicate(GUI* pGUI);
	double triarea(int, int, int, int, int, int);
	virtual bool point_included(int x, int y);
	virtual shape* Paste(Point);
	virtual void Move(Point P);
	void OPZOOM(double px, double py, double scale);
	void ResizeShape(double scale);  	//Resize a single triangle
	void RotateShape();  	//rotate a single triangle
};
