#include <iostream>
#include <Windows.h>

#include <fstream>
#include <string>

void waitForDebug(const std::string& fileName)
{
	int pid = GetCurrentProcessId();
	int count = 0;
	BOOL isDebugged = false;

	std::ostream *S = &std::cout;
	std::ofstream myfile;
	if (!fileName.empty())
	{
		myfile.open(fileName + std::to_string(pid) + ".log");
		if (myfile.is_open())
		{
			S = &myfile;
		}
	}

	while (!isDebugged && ++count < 1000)
	{
		isDebugged = IsDebuggerPresent();
		*S << pid << "   Waiting for debugger" << " " << isDebugged << std::endl;
		Sleep(2000);
	}
	*S << "Out" << std::endl;
	DebugBreak();
	*S << "After break" << std::endl;
}

int main(int argc, char** argv)
{
	std::cout << "Hello world" << std::endl;
	waitForDebug("c:\\tmp\\wait_debugger_");
}