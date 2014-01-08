/// @file
/// @author  Boris Mikic
/// @version 1.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://www.opensource.org/licenses/bsd-license.php

#include <hltypes/hstream.h>
#include <hltypes/hthread.h>

#include "Ip.h"
#include "PlatformSocket.h"
#include "sakit.h"
#include "Socket.h"
#include "SocketDelegate.h"
#include "ServerThread.h"
#include "TcpSocket.h"

namespace sakit
{
	extern harray<Base*> connections;
	extern hmutex connectionsMutex;

	ServerThread::ServerThread(PlatformSocket* socket, SocketDelegate* acceptedDelegate) :
		WorkerThread(&process, socket), state(Server::IDLE)
	{
		this->acceptedDelegate = acceptedDelegate;
	}

	ServerThread::~ServerThread()
	{
	}

	void ServerThread::_updateBinding()
	{
		if (!this->socket->bind(this->host, this->port))
		{
			this->mutex.lock();
			this->result = FAILED;
			this->mutex.unlock();
			return;
		}
		this->mutex.lock();
		this->result = FINISHED;
		this->mutex.unlock();
	}

	void ServerThread::_updateUnbinding()
	{
		if (!this->socket->disconnect())
		{
			this->mutex.lock();
			this->result = FAILED;
			this->mutex.unlock();
			return;
		}
		this->mutex.lock();
		this->result = FINISHED;
		this->mutex.unlock();
	}

	void ServerThread::_updateProcess()
	{
		switch (this->state)
		{
		case Server::BINDING:
			this->_updateBinding();
			break;
		case Server::RUNNING:
			this->_updateRunning();
			break;
		case Server::UNBINDING:
			this->_updateUnbinding();
			break;
		}
	}

	void ServerThread::process(hthread* thread)
	{
		((ServerThread*)thread)->_updateProcess();
	}

}
