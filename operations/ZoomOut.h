#pragma once
#include "operation.h"

//zoom out class
class opZoomOut : public operation
{
public:
	opZoomOut(controller* pCont);
	virtual ~opZoomOut();

	virtual void Execute();

};

