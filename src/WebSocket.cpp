/// @file
/// @author  Boris Mikic
/// @version 1.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://www.opensource.org/licenses/bsd-license.php

#include "WebSocket.h"

namespace sakit
{
	WebSocket::WebSocket(SocketDelegate* socketDelegate) : TcpSocket(socketDelegate)
	{
	}

	WebSocket::~WebSocket()
	{
	}
	
}