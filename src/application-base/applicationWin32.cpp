
ApplicationWin32::ApplicationWin32(HINSTANCE instance, UINT windowWidth, UINT windowHeight, const std::string &name, GraphicsDeviceType graphicsType, ApplicationCallback &callback) :
	m_callback(callback),
	m_window(*this)
{
	m_window.init(instance, windowWidth, windowHeight, name);

	switch(graphicsType)
	{
	case GraphicsDeviceTypeD3D11:
		m_graphics = new D3D11GraphicsDevice();
		break;
	default:
		MLIB_ERROR("invalid graphics device type");
	}
	m_graphics->init(m_window);

	m_data = new ApplicationData(&m_window, m_graphics);

	m_callback.init(*m_data);
}

ApplicationWin32::~ApplicationWin32()
{
	delete m_graphics;
	delete m_data;
}

void ApplicationWin32::messageLoop()
{
	bool messageReceived;
	MSG msg;
	msg.message = WM_NULL;
	PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );

	while( WM_QUIT != msg.message )
	{
		// Use PeekMessage() so we can use idle time to render the scene. 
		messageReceived = ( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) != 0 );

		if( messageReceived )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			m_graphics->renderBeginFrame();
			m_callback.render(*m_data);
			m_graphics->renderEndFrame();
		}
	}
}