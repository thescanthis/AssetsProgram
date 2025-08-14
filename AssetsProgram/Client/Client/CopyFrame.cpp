#include "pch.h"
#include "CopyFrame.h"
#include "CompanyInfo.h"
#include "CompanyInfoDetail.h"
#include "ClientInfo.h"
#include "InventoryAdd.h"
#include "InventorySearch.h"

CopyFrame::CopyFrame(wxWindow* parent, const wxString&)
	:SubFrame(parent,"����")
{
	int32 idx = 0;

	wxString string[4][2] = { {"ȸ�����","������"},{}};
	for (int32 i = 0; i < 2; i++)
	{
		auto* rowSizer = new wxBoxSizer(wxHORIZONTAL);
		for (int j = 0; j < 4; j++)
		{
			CompanyPanels.push_back(new CompanyInfo(this, string[i][j]));
			rowSizer->Add(CompanyPanels.back(), 0, wxALL, 16); // ī�� ���� 10px
		}
		GetContentSizer()->Add(rowSizer, 0, wxALIGN_CENTER); // ��� ����
	}

	if (CompanyPanels.size() >= 2) {
		// 0��: ȸ���Է� / ����߰�
		CompanyPanels[0]->AddButton("ȸ������", MakeSingletonOpener<CompanyInfoDetail>(this,"ȸ������"), 8);
		CompanyPanels[0]->AddButton("�ŷ�ó����",MakeSingletonOpener<ClientInfo>(this,"�ŷ�ó����"), 8);
		CompanyPanels[0]->GetContentSizer()->AddStretchSpacer(); // �Ʒ� ���� �о��(����)

		// 1��: �ŷ�ó���� / �����ȸ
		CompanyPanels[1]->AddButton("�����ȸ",MakeSingletonOpener<InventoryAdd>(this),8);
		CompanyPanels[1]->AddButton("����߰�", MakeSingletonOpener<InventorySearch>(this),8);
		CompanyPanels[1]->GetContentSizer()->AddStretchSpacer(); // ����
	}

    Layout();
}

CopyFrame::~CopyFrame()
{
	singletons_.clear();
}

void CopyFrame::OpenInventoryAdd()
{
	wxMessageBox("����߰�");
}

void CopyFrame::OpenPartnerInfo()
{
	wxMessageBox("�ŷ�ó����");
}

void CopyFrame::OpenInventoryQuery()
{
	wxMessageBox("�����ȸ");
}