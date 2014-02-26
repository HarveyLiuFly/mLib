
class Clock
{
public:
    Clock();
    void start();
    double elapsed();

	inline UINT64 startTime()
	{
		return m_startTime;
	}
	inline UINT64 ticksPerSecond()
	{
		return m_ticksPerSecond;
	}

private:
    UINT64 m_startTime;
    UINT64 m_ticksPerSecond;
};

class ComponentTimer
{
public:
	ComponentTimer(const std::string &prompt)
	{
		m_prompt = prompt;
		m_terminated = false;
		Console::log("start " + prompt);
	}
	~ComponentTimer()
	{
		if(!m_terminated) end();
	}
	void end()
	{
		m_terminated = true;
		Console::log("end " + m_prompt + ", " + std::to_string(m_clock.elapsed()) + "s");
	}

private:
	std::string m_prompt;
	Clock m_clock;
	bool m_terminated;
};