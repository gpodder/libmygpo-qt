/***************************************************************************
* This file is part of libmygpo-qt                                         *
* Copyright (c) 2010 - 2012 Stefan Derkits <stefan@derkits.at>             *
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

#include "Config_p.h"
#include "Version.h"

#include <QString>
#include <QStringBuilder>
#include <QLatin1String>

using namespace mygpo;

Config* Config::s_instance = 0;

ConfigPrivate::ConfigPrivate( Config* qq ) : q( qq )
{
  
}

ConfigPrivate::~ConfigPrivate()
{
  
}

int ConfigPrivate::majorVersion() const
{
    return MYGPO_QT_VERSION_MAJOR;
}

int ConfigPrivate::minorVersion() const
{
    return MYGPO_QT_VERSION_MINOR;
}

int ConfigPrivate::patchVersion() const
{
    return MYGPO_QT_VERSION_PATCH;
}

QString ConfigPrivate::version() const
{
    return QString( majorVersion() ) % QLatin1String( "." ) % QString( minorVersion() ) % QLatin1String( "." ) % QString( patchVersion() );
}

Config::Config() : d( new ConfigPrivate( this ) )
{

}

Config::~Config()
{
    delete d;
}

int Config::majorVersion() const
{
    return d->majorVersion();
}

int Config::minorVersion() const
{
    return d->minorVersion();
}


int Config::patchVersion() const
{
    return d->patchVersion();
}

QString Config::version() const
{
    return d->version();
}

Config* Config::instance()
{
    if ( !s_instance ) {
        s_instance = new Config;
    }

    return s_instance;
}
