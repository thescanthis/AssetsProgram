#include "pch.h"
#include "WidgetParent.h"

WidgetParent::WidgetParent(wxWindow* parent, const wxString Title)
	:wxFrame(parent, wxID_ANY, Title, wxDefaultPosition, wxSize(800, 600))
{
}

WidgetParent::~WidgetParent()
{
}