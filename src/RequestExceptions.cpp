/***************************************************************************
* This file is part of libmygpo-qt                                         *
* Copyright (c) 2010 Stefan Derkits <stefan@derkits.at>                    *
* Copyright (c) 2010 Christian Wagner <christian.wagner86@gmx.at>          *
* Copyright (c) 2010 Felix Winter <ixos01@gmail.com>                       *
*                                                                          *
* This library is free software; you can redistribute it and/or            *
* modify it under the terms of the GNU Lesser General Public               *
* License as published by the Free Software Foundation; either             *
* version 2.1 of the License, or (at your option) any later version.       *
*                                                                          *
* This library is distributed in the hope that it will be useful,          *
* but WITHOUT ANY WARRANTY; without even the implied warranty of           *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU        *
* Lesser General Public License for more details.                          *
*                                                                          *
* You should have received a copy of the GNU Lesser General Public         *
* License along with this library; if not, write to the Free Software      *
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 *
* USA                                                                      *
***************************************************************************/

#include "RequestExceptions.h"
#include <QLatin1String>

using namespace mygpo;

RequestException::RequestException(const QString &s, int errorFlag)
					: std::runtime_error(s.toStdString()), errorFlag(errorFlag) { }

InvalidDeviceIdException::InvalidDeviceIdException()
					: RequestException(QLatin1String("Invalid device id."), 203) { }

InvalidUserException::InvalidUserException()
					: RequestException(QLatin1String("Invalid username."), 201) { }

InvalidAuthException::InvalidAuthException()
					: RequestException(QLatin1String("Authentication failed."), 201) { }

ServerNotFoundException::ServerNotFoundException()
					: RequestException(QLatin1String("Server not found."), 204) { }
