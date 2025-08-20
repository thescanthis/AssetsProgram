#pragma once
#include "Types.h"

static void GridLabelInitilize(wxGrid* m_grid, const wxString LabelStr[],bool Enable=false)
{
	// 그리드 만든 뒤
	m_grid->SetDefaultCellAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// 헤더(라벨)도 가운데
	m_grid->SetColLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);
	m_grid->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	int size = m_grid->GetNumberCols();
	for (int32 i = 0; i < size; i++)
	{
		m_grid->SetColLabelValue(i, LabelStr[i]);
	}

	// 모양/동작 기본값
	m_grid->EnableEditing(Enable);                 // 읽기 전용(원하면 true)
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