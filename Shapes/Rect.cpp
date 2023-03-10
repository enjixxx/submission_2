#include "Rect.h"
#include "algorithm"

Rect::Rect()
{}

Rect::Rect(Point P1, Point P2, GfxInfo shapeGfxInfo):shape(shapeGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	Center.x = (Corner1.x + Corner2.x) / 2;
	Center.y = (Corner1.y + Corner2.y) / 2;
}


Rect::~Rect()
{}

int* Rect::Getshapeinfo()
{
	int listofparameters[4];
	if (Corner1.x < Corner2.x && Corner1.y < Corner2.y) {
		listofparameters[0] = Corner1.x - 10;
		listofparameters[1] = Corner1.y - 10;
		listofparameters[2] = abs(Corner1.x - Corner2.x) + 15;
		listofparameters[3] = abs(Corner1.y - Corner2.y) + 15;
		return listofparameters;
	}
	if (Corner1.x > Corner2.x && Corner1.y < Corner2.y) {
		listofparameters[0] = Corner2.x - 10;
		listofparameters[1] = Corner1.y - 10;
		listofparameters[2] = abs(Corner1.x - Corner2.x) + 15;
		listofparameters[3] = abs(Corner1.y - Corner2.y) + 15;
		return listofparameters;
	}
	if (Corner1.x > Corner2.x && Corner1.y > Corner2.y) {
		listofparameters[0] = Corner2.x - 10;
		listofparameters[1] = Corner2.y - 10;
		listofparameters[2] = abs(Corner1.x - Corner2.x) + 15;
		listofparameters[3] = abs(Corner1.y - Corner2.y) + 15;
		return listofparameters;
	}
	if (Corner1.x < Corner2.x && Corner1.y > Corner2.y) {
		listofparameters[0] = Corner1.x - 10;
		listofparameters[1] = Corner2.y - 10;
		listofparameters[2] = abs(Corner1.x - Corner2.x) + 15;
		listofparameters[3] = abs(Corner1.y - Corner2.y) + 15;
		return listofparameters;
	}
}

void Rect::Move(Point P)
{
	

	double length = abs(Corner2.x - Corner1.x);
	double width = abs(Corner1.y - Corner2.y);
	Corner1.x = P.x - length / 2;
	Corner1.y = P.y + width / 2;
	Corner2.x = P.x + length / 2;
	Corner2.y = P.y - width / 2;


}
void Rect::Save(ofstream& OutFile)
{
	OutFile << "RECTANGLE" << " " << Corner1.x << " " << Corner1.y << " " << Corner2.x << " " << Corner2.y << " " << (ShpGfxInfo.isFilled) << " " << to_string(ShpGfxInfo.FillClr.ucRed) << " " << to_string(ShpGfxInfo.FillClr.ucGreen) << " " << to_string(ShpGfxInfo.FillClr.ucBlue) << " " << to_string(ShpGfxInfo.DrawClr.ucRed) << " " << to_string(ShpGfxInfo.DrawClr.ucGreen) << " " << to_string(ShpGfxInfo.DrawClr.ucBlue) << " " << (ShpGfxInfo.BorderWdth) << endl;

}

void Rect::hideShape(GUI* pUI)
{
	//pUI->StickImage("images\\MenuIcons\\image.jpg", Corner1.x, Corner1.y, 200, 200);
}

void Rect::Load(ifstream& inFile)
{
	type = "Rect";
	int x;
	string jump;

	inFile >> x;
	Corner1.x = x;

	inFile >> x;
	Corner1.y = x;

	inFile >> x;

	Corner2.x = x;

	inFile >> x;
	Corner2.y = x;

	inFile >> x;
	if (x == 0)
	{
		ShpGfxInfo.isFilled = FALSE;

	}
	else if (x == 1)
	{
		ShpGfxInfo.isFilled = TRUE;

	}
	inFile >> jump;

	ShpGfxInfo.FillClr.ucRed = stoi(jump);
	inFile >> jump;

	ShpGfxInfo.FillClr.ucGreen = stoi(jump);
	inFile >> jump;

	ShpGfxInfo.FillClr.ucBlue = stoi(jump);
	inFile >> jump;

	ShpGfxInfo.DrawClr.ucRed = stoi(jump);
	inFile >> jump;

	ShpGfxInfo.DrawClr.ucGreen = stoi(jump);
	inFile >> jump;

	ShpGfxInfo.DrawClr.ucBlue = stoi(jump);
	inFile >> x;

	ShpGfxInfo.BorderWdth = x;

	ShpGfxInfo.isSelected = FALSE;
}


Rect::Rect(const Rect* copy) :shape(copy->ShpGfxInfo)
{
	this->Corner1 = copy->Corner1;
	this->Corner2 = copy->Corner2;
	this->ID = copy->ID;
}

shape* Rect::clone()
{
	shape* newShape = new Rect(*this);

	return newShape;
}


shape* Rect::duplicate(GUI* pGUI) {
	Point p1, p2;
	p1.x = Corner1.x + 250;
	p1.y = Corner1.y;
	p2.x = Corner2.x + 250;
	p2.y = Corner2.y;
	GfxInfo info = ShpGfxInfo;
	ShpGfxInfo.isDuplicated = true;
	Rect* L = new Rect(p1, p2, info);
	return L;
}


void Rect::Draw(GUI* pUI) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pUI->DrawRect(Corner1, Corner2, ShpGfxInfo);
}
bool Rect::point_included(int x, int y) {

	if ((Corner1.x < Corner2.x && Corner1.y < Corner2.y) && (x > Corner1.x && x<Corner2.x && y>Corner1.y && y < Corner2.y)) {
		return true;
	}
	else if ((Corner1.x < Corner2.x && Corner1.y > Corner2.y) && (x > Corner1.x && x<Corner2.x && y>Corner2.y && y < Corner1.y)) {
		return true;
	}
	else if ((Corner1.x > Corner2.x && Corner1.y < Corner2.y) && (x > Corner2.x && x<Corner1.x && y>Corner1.y && y < Corner2.y))
		return true;
	else if ((Corner1.x > Corner2.x && Corner1.y > Corner2.y) && (x > Corner2.x && x<Corner1.x && y>Corner2.y && y < Corner1.y))
		return true;
	else
		return false;
}
void  Rect::OPZOOM(double px, double py, double scale)   //function to zoom in or out according to the value of the scale factor
{
	Corner1.x = (Corner1.x * scale) - (scale * px) + px;
	Corner2.x = (Corner2.x * scale) - (scale * px) + px;
	Corner1.y = (Corner1.y * scale) - (scale * py) + py;
	Corner2.y = (Corner2.y * scale) - (scale * py) + py;
}
void Rect::ResizeShape(double scale)  	//Resize a single rectangle
{
	Corner1.x = (Corner1.x * scale) - (Center.x * scale) + Center.x;
	Corner2.x = (Corner2.x * scale) - (Center.x * scale) + Center.x;
	Corner1.y = (Corner1.y * scale) - (Center.y * scale) + Center.y;
	Corner2.y = (Corner2.y * scale) - (Center.y * scale) + Center.y;
}

void Rect::RotateShape()  	//Rotate a single rectangle
{
	int C1x = Corner1.x;
	int C2x = Corner2.x;
	int C1y = Corner1.y;
	int C2y = Corner2.y;
    Corner1.x =  Center.y + Center.x - C1y;
	Corner2.x = Center.y + Center.x - C2y;
	Corner1.y = C1x+ Center.y - Center.x;
	Corner2.y = C2x + Center.y - Center.x;

}
void Rect::Scramble(int i, int j)
{
	
	Corner1.x = i - 80;
	Corner1.y = j - 40;
	Corner2.x = i + 80;
	Corner2.y = j + 40;

}