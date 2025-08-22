#include "pch.h"
#include "CopyFrame.h"
#include "CompanyInfo.h"
#include "CompanyInfoDetail.h"
#include "productInfo.h"
#include "ClientInfo.h"
#include "InventorySearch.h"
#include "ClientOrderManage.h"

CopyFrame::CopyFrame(wxWindow* parent, const wxString&)
	:SubFrame(parent,"없음")
{
	int32 idx = 0;

	wxString string[4][2] = 
	{ 
		{"회사정보","재고관리"},
		{}
	};

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
		CompanyPanels[0]->AddButton("회사정보", G_Template->MakeSingletonOpener<CompanyInfoDetail>(this,"회사정보"), 8);
		CompanyPanels[0]->AddButton("상품정보", G_Template->MakeSingletonOpener<ProductInfo>(this, "상품정보"), 8);
		CompanyPanels[0]->AddButton("거래처정보", G_Template->MakeSingletonOpener<ClientInfo>(this,"거래처정보"), 8);
		CompanyPanels[0]->GetContentSizer()->AddStretchSpacer(); // 아래 공간 밀어내기(선택)

		// 1번: 거래처정보 / 재고조회
		CompanyPanels[1]->AddButton("발주관리", G_Template->MakeSingletonOpener<ClientOrderManage>(this, "발주관리"), 8);
		CompanyPanels[1]->AddButton("재고관리", G_Template->MakeSingletonOpener<InventorySearch>(this, "재고관리"), 8);
		CompanyPanels[1]->GetContentSizer()->AddStretchSpacer(); // 선택
	}

    Layout();
}

CopyFrame::~CopyFrame()
{
	CompanyPanels.clear();
}