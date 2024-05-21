#include "Application.h"

wxIMPLEMENT_APP(Application);

Application::Application()
{
}


Application::~Application()
{
}

bool Application::OnInit()
{
	m_frame = new MainFrame();
	m_frame->Show();

	return true;
}
