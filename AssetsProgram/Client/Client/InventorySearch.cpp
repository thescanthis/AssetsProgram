#include "pch.h"
#include "InventorySearch.h"

InventorySearch::InventorySearch(wxWindow* parent)
	: wxFrame(parent, wxID_ANY, "�����ȸ", wxDefaultPosition, wxSize(800, 600))
{
	SetSizeHints(800, 600, 800, 600);         // ���� ũ��(���ϸ� ����)


	Center();
}

InventorySearch::~InventorySearch()
{

}
