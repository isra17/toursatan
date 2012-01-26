#ifndef CCONNECTION_H
#define CCONNECTION_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <string>
#include <vector>
#include <algorithm>

#include "../../Misc/BasicType.h"

//!Connexion socket
class CConnection
{
public:
	CConnection(boost::asio::io_service& ioService) : m_socket(ioService)
	{

	}

	boost::asio::ip::tcp::socket& socket()
	{
		return m_socket;
	}


	//!Start write operation
	template <typename Handler>
	void asyncWrite(const std::string& data, Handler handler)
	{
		//! Write the serialized data to the socket. We use "gather-write" to send
		//! both the header and the data in a single write operation.
		assert(m_socket.is_open());
		UInt16 size = data.size();
		std::vector<boost::asio::const_buffer> buffers;
		buffers.push_back(boost::asio::buffer(&size,HEADER_SIZE));
		buffers.push_back(boost::asio::buffer(data));
		
		boost::asio::async_write(m_socket, buffers, handler);
	}


	//!Start read operation
	template <typename Handler>
	void asyncRead(std::string& data, Handler handler)
	{
		boost::asio::async_read(m_socket, boost::asio::buffer(m_readHeader,HEADER_SIZE),
			boost::bind(&CConnection::handleReadHeader<Handler>,
				this, boost::asio::placeholders::error, boost::ref(data),
				boost::make_tuple(handler)));
	}


private:
	//!Recoit le nombre d'octet composant le message
	template <typename Handler>
	void handleReadHeader(const boost::system::error_code& e,
		std::string& data, boost::tuple<Handler> handler)
	{
		if (e)
		{
			boost::get<0>(handler)(e);
		}
		else
		{
			// Start an asynchronous call to receive the data.
			m_readData.resize(*((UInt16*)m_readHeader));

			boost::asio::async_read(m_socket, boost::asio::buffer(m_readData),
				boost::bind(&CConnection::handleReadData<Handler>, this,
					boost::asio::placeholders::error, boost::ref(data), handler));
		}
	}



	template <typename Handler>
	void handleReadData(const boost::system::error_code& e,
		std::string& data, boost::tuple<Handler> handler)
	{
		if (e)
		{
			boost::get<0>(handler)(e);
		}
		else
		{
			data.resize(m_readData.size());
			std::copy(m_readData.begin(),m_readData.end(),data.begin());
			// Inform caller that data has been received ok.
			boost::get<0>(handler)(e);
		}
	}


	//Connection socket
	boost::asio::ip::tcp::socket m_socket;

	//Header buffer (2 octet (short int)
	static const int HEADER_SIZE = 2;
	char m_readHeader[HEADER_SIZE];

	std::vector<char> m_readData;

};

typedef boost::shared_ptr<CConnection> CConnection_ptr;


#endif

