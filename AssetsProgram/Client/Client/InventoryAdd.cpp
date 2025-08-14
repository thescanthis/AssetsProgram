#include "pch.h"
#include "InventoryAdd.h"

InventoryAdd::InventoryAdd(wxWindow* parent)
	:wxFrame(parent, wxID_ANY, "재고추가", wxDefaultPosition, wxSize(800, 600))
{
	SetSizeHints(800, 600, 800, 600);         // 고정 크기(원하면 제거)


	Center();
}

InventoryAdd::~InventoryAdd()
{
}
