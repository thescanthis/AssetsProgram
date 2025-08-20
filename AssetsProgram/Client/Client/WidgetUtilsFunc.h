#pragma once
#include "Types.h"

static void GridLabelInitilize(wxGrid* m_grid, const wxString LabelStr[],bool Enable=false)
{
	// �׸��� ���� ��
	m_grid->SetDefaultCellAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// ���(��)�� ���
	m_grid->SetColLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);
	m_grid->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	int size = m_grid->GetNumberCols();
	for (int32 i = 0; i < size; i++)
	{
		m_grid->SetColLabelValue(i, LabelStr[i]);
	}

	// ���/���� �⺻��
	m_grid->EnableEditing(Enable);                 // �б� ����(���ϸ� true)
	m_grid->SetSelectionMode(wxGrid::wxGridSelectRows);
	m_grid->EnableGridLines(true);
	m_grid->SetRowLabelSize(40);
	m_grid->SetColLabelSize(28);
	m_grid->SetDefaultRowSize(24);
}

static void GridColumnInitilize(wxGrid* m_grid,const int Wid[])
{
	int size = m_grid->GetNumberCols();
	for (int32 i = 0; i < size; i++)
		m_grid->SetColSize(i, Wid[i]);
}