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

#include "AddRemoveResult.h"

using namespace mygpo;

AddRemoveResult::AddRemoveResult(qulonglong timestamp, const QList< QPair< QUrl, QUrl > >& updateUrls, QObject* parent): QObject(parent), m_timestamp(timestamp), m_updateUrls(updateUrls)
{

}

AddRemoveResult::AddRemoveResult(const AddRemoveResult& other): QObject(other.parent()), m_timestamp(other.timestamp()), m_updateUrls(other.updateUrls())
{

}

AddRemoveResult AddRemoveResult::operator=(const AddRemoveResult& other)
{
    return AddRemoveResult(other);
}

const qulonglong AddRemoveResult::timestamp() const
{
    return m_timestamp;
}

const QList< QPair< QUrl, QUrl > > AddRemoveResult::updateUrls() const
{
    return m_updateUrls;
}
