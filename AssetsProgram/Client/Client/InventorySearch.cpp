#include "pch.h"
#include "InventorySearch.h"

InventorySearch::InventorySearch(wxWindow* parent)
	: wxFrame(parent, wxID_ANY, "재고조회", wxDefaultPosition, wxSize(800, 600))
{
	SetSizeHints(800, 600, 800, 600);         // 고정 크기(원하면 제거)


	Center();
}

InventorySearch::~InventorySearch()
{

}
