#include <SFML/System.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>

#include "Engine/CClientGameEngine.h"
#include "Engine/CServerGameEngine.h"
#include "Engine/Event/CEventEngine.h"
#include "Engine/Event/CMsgEvent.h"

#include "Engine/Event/Network/CConnection.h"
#include "Engine/Misc/CTourException.h"
#include "Engine/Misc/BasicType.h"

#include <string>
#include <boost/program_options.hpp>

using namespace boost::program_options;

void startServer()
{
	system("Tour.exe --s --n=1");
}

void startClient()
{
	system("Tour.exe --c");
}

int main(int argc, char* argv[])
{	
	///*
	try{
		options_description optDesc("Listes des options");
		optDesc.add_options()
			("help", "Produces help message")
			("s", "Start server")
			("c", "Start client")
			("cs", "Start client then server (Used for debugging)")
			("sc", "Start server then client (Used for debugging)")
			("h", value<std::string>()->default_value("127.0.0.1"), "Server adresse (Client only)")
			("p", value<std::string>()->default_value("12345"), "Server port")
			("n", value<UInt16>()->default_value(2), "Client count (Server only)")
			("width", value<UInt16>()->default_value(1024), "Screen width")
			("height", value<UInt16>()->default_value(768), "Screen Height");

		variables_map vm;
		store(parse_command_line(argc, argv, optDesc), vm);
		notify(vm);  

		if(vm.count("s"))
			CServerGameEngine::init(vm);
		else if(vm.count("c"))
			CClientGameEngine::init(vm);
		else if(vm.count("cs"))
		{
			boost::thread serverThread(startServer);
			sf::Sleep(2.f);
			CClientGameEngine::init(vm);
		}
		else if(vm.count("sc"))
		{
			CServerGameEngine::init(vm);
			boost::thread clientThread(startClient);
		}
		else
		{
			std::cout << optDesc << std::endl;
			throw(CTourException("Parametre manquant"));
		}
		
		return CGameEngine::instance()->run();
	}
	catch(CTourException e)
	{
		std::cerr << "Tour exception : " << e.what();
	}
	catch(boost::program_options::error e)
	{
		std::cerr << e.what();
	}
	catch(boost::system::system_error e)
	{
		std::cerr << e.what();
	}
	catch(std::exception e)
	{
		std::cerr << e.what();
	}
	catch(...)
	{
		std::cerr << "...";
	}
	//*/

	getchar();

	return 0;
}