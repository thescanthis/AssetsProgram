#pragma once
#include "Types.h"

namespace WU {

	inline void GridLabelInitilize(wxGrid* m_grid, const wxArrayString headers, bool Enable = false, int32 RowLabelSize = 40);
	inline void GridColumnInitilize(wxGrid* m_grid, const int Wid[]);
	
	template<class T>
	inline wxGrid* MakeGrid(wxWindow* parent, const wxArrayString headers, const int32 wid[], wxEventTypeTag<wxGridEvent> event, void(T::* OnGridDClick)(wxGridEvent&), T* receiver, int32 row = 0)
	{
		auto* g = new wxGrid(parent, wxID_ANY);
		g->CreateGrid(row, headers.GetCount());
		// 라벨/정렬/행번호 숨김
		GridLabelInitilize(g, headers);
		GridColumnInitilize(g, wid);

		g->Bind(event, OnGridDClick, receiver);
		return g;
	}

	inline void GridLabelInitilize(wxGrid* m_grid, const wxArrayString headers, bool Enable, int32 RowLabelSize)
	{
		// 그리드 만든 뒤
		m_grid->SetDefaultCellAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

		// 헤더(라벨)도 가운데
		m_grid->SetColLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);
		m_grid->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

		int size = m_grid->GetNumberCols();
		for (int32 i = 0; i < size; i++)
		{
			m_grid->SetColLabelValue(i, headers[i]);
		}

		// 모양/동작 기본값
		m_grid->EnableEditing(Enable);                 // 읽기 전용(원하면 true)
		m_grid->SetSelectionMode(wxGrid::wxGridSelectRows);
		m_grid->EnableGridLines(true);
		m_grid->SetRowLabelSize(RowLabelSize);
		m_grid->SetColLabelSize(28);
		m_grid->SetDefaultRowSize(24);
	}
	inline void GridColumnInitilize(wxGrid* m_grid, const int Wid[])
	{
		int size = m_grid->GetNumberCols();
		for (int32 i = 0; i < size; i++)
			m_grid->SetColSize(i, Wid[i]);

		// 그리드가 계산한 권장 크기 + 10px
		wxSize bs = m_grid->GetBestSize();
		bs.IncBy(20, 0);                  // X축만 +10
		m_grid->SetMinSize(bs);           // 최소 크기로 고정
		m_grid->GetParent()->Layout();    // 레이아웃 갱신
	}
}