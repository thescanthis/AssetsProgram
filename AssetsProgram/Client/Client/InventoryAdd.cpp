#include "pch.h"
#include "InventoryAdd.h"
#include <wx/treectrl.h>

InventoryAdd::InventoryAdd(wxWindow* parent, const wxString Title) : WidgetParent(parent, Title)
{
	SetSizeHints(800, 600, 800, 600);         // 고정 크기(원하면 제거)

	
	Center();
}

InventoryAdd::~InventoryAdd()
{
}

void InventoryAdd::BtnTitleInit()
{

}

void InventoryAdd::LeftBodyInit()
{
}

void InventoryAdd::InfoTitleInit()
{
}

void InventoryAdd::RightBodyInit()
{
}
