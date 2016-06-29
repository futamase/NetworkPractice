#include <boost\asio.hpp>
#include <iostream>

using namespace std;
using namespace boost::asio;
using ip::tcp;

int main()
{
	io_service io;

	tcp::acceptor acc(io, tcp::endpoint(tcp::v4(), 31400));

	while (1)
	{
		tcp::iostream s;
		acc.accept(*s.rdbuf());

		cout << "[connect start]" << endl;

		cout << "[connect end]" << endl;
	}
}
