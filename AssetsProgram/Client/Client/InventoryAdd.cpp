#include "pch.h"
#include "InventoryAdd.h"

InventoryAdd::InventoryAdd(wxWindow* parent)
	:wxFrame(parent, wxID_ANY, "����߰�", wxDefaultPosition, wxSize(800, 600))
{
	SetSizeHints(800, 600, 800, 600);         // ���� ũ��(���ϸ� ����)


	Center();
}

InventoryAdd::~InventoryAdd()
{
}
