#include "pch.h"
#include "CopyFrame.h"
#include "CompanyInfo.h"
#include "CompanyInfoDetail.h"
#include "ClientInfo.h"
#include "InventoryAdd.h"
#include "InventorySearch.h"

CopyFrame::CopyFrame(wxWindow* parent, const wxString&)
	:SubFrame(parent,"없음")
{
	int32 idx = 0;

	wxString string[4][2] = { {"회사관리","재고관리"},{}};
	for (int32 i = 0; i < 2; i++)
	{
		auto* rowSizer = new wxBoxSizer(wxHORIZONTAL);
		for (int j = 0; j < 4; j++)
		{
			CompanyPanels.push_back(new CompanyInfo(this, string[i][j]));
			rowSizer->Add(CompanyPanels.back(), 0, wxALL, 16); // 카드 간격 10px
		}
		GetContentSizer()->Add(rowSizer, 0, wxALIGN_CENTER); // 가운데 정렬
	}

	if (CompanyPanels.size() >= 2) {
		// 0번: 회사입력 / 재고추가
		CompanyPanels[0]->AddButton("회사정보", MakeSingletonOpener<CompanyInfoDetail>(this,"회사정보"), 8);
		CompanyPanels[0]->AddButton("거래처정보",MakeSingletonOpener<ClientInfo>(this,"거래처정보"), 8);
		CompanyPanels[0]->GetContentSizer()->AddStretchSpacer(); // 아래 공간 밀어내기(선택)

		// 1번: 거래처정보 / 재고조회
		CompanyPanels[1]->AddButton("재고조회",MakeSingletonOpener<InventoryAdd>(this),8);
		CompanyPanels[1]->AddButton("재고추가", MakeSingletonOpener<InventorySearch>(this),8);
		CompanyPanels[1]->GetContentSizer()->AddStretchSpacer(); // 선택
	}

    Layout();
}

CopyFrame::~CopyFrame()
{
	singletons_.clear();
}

void CopyFrame::OpenInventoryAdd()
{
	wxMessageBox("재고추가");
}

void CopyFrame::OpenPartnerInfo()
{
	wxMessageBox("거래처정보");
}

void CopyFrame::OpenInventoryQuery()
{
	wxMessageBox("재고조회");
}