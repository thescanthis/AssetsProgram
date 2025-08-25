#include "pch.h"
#include "MainFrame.h"
#include "ClientPacketHandler.h"
#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"
#include "ClientPacketHandler.h"


class ServerSession : public PacketSession
{
public:
	~ServerSession()
	{
		cout << "~ServerSession" << endl;
	}

	virtual void OnConnected() override
	{
		cout << "OnConnected" << endl;

		Protocol::C_ENTER_GAME pkt;
		auto sendBuffer = ClientPacketHandler::MakeSendBuffer(pkt);
		Send(sendBuffer);
	}

	virtual void OnRecvPacket(BYTE* buffer, int32 len) override
	{
		PacketSessionRef session = GetPacketSessionRef();
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

		// TODO : packetId 대역 체크
		ClientPacketHandler::HandlePacket(session, buffer, len);
	}

	virtual void OnSend(int32 len) override
	{
		cout << "OnSend Len = " << len << endl;
	}

	virtual void OnDisconnected() override
	{
		cout << "Disconnected" << endl;
	}
};


TemplateFunc* G_Template = nullptr;
DBTest* DBMaps = nullptr;

class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        wxInitAllImageHandlers(); // wxImage용 초기화

        G_Template = new TemplateFunc();
        DBMaps = new DBTest();

        frame = new MainFrame();
        frame->Show();
        SetTopWindow(frame);
        SetExitOnFrameDelete(true);  // 이거 설정했으면 프레임이 닫힐 때 delete 됨

		CallAfter([this] {StartNetwork(); });

        return true;
    }

	void StartNetwork()
	{
		ClientPacketHandler::Init();
		this_thread::sleep_for(1s);

		this->service = make_shared<ClientService>(
			NetAddress(L"172.30.1.13", 7777),
			make_shared<IocpCore>(),
			[=]() {return make_shared<ServerSession>(); },
			1);

		ASSERT_CRASH(service->Start());

		for (int32 i = 0; i < 2; i++)
		{
			GThreadManager->Launch([=]()
				{
					while (true)
					{
						service->GetIocpCore()->Dispatch();
					}
				});
		}

		this->m_tick.SetOwner(this);
		Bind(wxEVT_TIMER, [this](wxTimerEvent&) {
			//service->Broadcast(sendBuffer);
			}, this->m_tick.GetId());
		this->m_tick.Start(1000);
	}

    virtual int OnExit() override {
        delete G_Template;
        delete DBMaps;
		m_tick.Stop();
		GThreadManager->Join();
        wxImage::CleanUpHandlers(); // 정리 작업
        return wxApp::OnExit();
    }

private:
    MainFrame*		 frame = nullptr;
	ClientServiceRef service;
	wxTimer          m_tick;   // 주기 작업(예: 브로드캐스트)용
};

wxIMPLEMENT_APP(MyApp);