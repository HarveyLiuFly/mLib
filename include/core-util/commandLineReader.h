
class CommandLineReader
{
public:
	CommandLineReader(const std::string &usage, int argc, char* argv[])
	{
		m_commandLine = "";
		for(int arg = 1; arg < argc; arg++)
			m_commandLine += argv[arg];
		m_args = StringUtil::split(m_commandLine, " ");
		//m_args = m_commandLine.split(" ");
		m_usage = usage;
	}

	CommandLineReader(const std::string &usage, const std::string &commandLine)
	{
		m_commandLine = commandLine;
		m_args = StringUtil::split(m_commandLine, " ");
		//m_args = commandLine.split(" ");
		m_usage = usage;
	}

	const Vector<std::string>& args() const
	{
		return m_args;
	}

	const std::string arg(UINT argIndex) const
	{
		if(argIndex >= m_args.size())
		{
			Console::log("insufficient number of arguments: " + m_commandLine);
			Console::log("usage: " + m_usage);
			MLIB_ERROR("aborting");
			exit(1);
		}
		return m_args[argIndex];
	}

	bool hasArgWithPrefix(const std::string &prefix) const
	{
		return (m_args.findFirstIndex([prefix](const std::string &s) { return StringUtil::startsWith(s, prefix); }) != -1);
	}



private:
	Vector<std::string> m_args;
	std::string m_commandLine;
	std::string m_usage;
};