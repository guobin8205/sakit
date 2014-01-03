/// @file
/// @author  Boris Mikic
/// @version 1.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://www.opensource.org/licenses/bsd-license.php
/// 
/// @section DESCRIPTION
/// 
/// Defines a platform dependent implementation for socket functionality.

#ifndef SAKIT_PLATFORM_SOCKET_H
#define SAKIT_PLATFORM_SOCKET_H

#include <hltypes/harray.h>
#include <hltypes/hltypesUtil.h>
#include <hltypes/hmutex.h>
#include <hltypes/hplatform.h>
#include <hltypes/hsbase.h>
#include <hltypes/hstring.h>
#include <hltypes/hthread.h>

#include "Ip.h"
#include "sakitExport.h"

namespace sakit
{
	class Socket;

	class sakitExport PlatformSocket
	{
	public:
		PlatformSocket();
		~PlatformSocket();

		HL_DEFINE_IS(connected, Connected);

		bool connect(Ip host, unsigned int port);
		bool bind(Ip host, unsigned int port);
		bool disconnect();
		bool send(hsbase* stream, int& sent);
		bool receive(hsbase* stream, hmutex& mutex, int& maxBytes);
		bool listen();
		bool accept(Socket* socket);

		static void platformInit();
		static void platformDestroy();

	protected:
		bool connected;
		char* sendBuffer;
		char* receiveBuffer;
		fd_set readSet;

#if !defined(_WIN32) || !defined(_WINRT)
		unsigned int sock;
		struct addrinfo* info;
		struct sockaddr_storage* address;
#else
		Windows::Networking::Sockets::StreamSocket^ sock;
		Windows::Networking::HostName^ hostName;
		bool _asyncProcessing;
		bool _asyncFinished;
		unsigned int _asyncSize;
		bool _awaitAsync();
#endif

		bool _createSocket(Ip host, unsigned int port);
		bool _finishSocket(int result, chstr functionName);
		int _printLastError();

		bool _setNonBlocking(bool value);

	};

}
#endif