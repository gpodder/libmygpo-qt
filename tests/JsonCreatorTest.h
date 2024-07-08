/***************************************************************************
* This file is part of libmygpo-qt                                         *
* Copyright (c) 2012 Stefan Derkits <stefan@derkits.at>                    *
* Copyright (c) 2012 Felix Winter <ixos01@gmail.com>                       *
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

#ifndef JSONCREATORTEST_H
#define JSONCREATORTEST_H

#include "JsonCreator.h"

#include <QtTest/QtTest>

namespace mygpo {

/**
 * This class tests methods of the JsonCreator class
 */
class JsonCreatorTest : public QObject {
  Q_OBJECT
public:
  JsonCreatorTest();
  virtual ~JsonCreatorTest();
private Q_SLOTS:
  void initTestCase();
  void cleanupTestCase();
  void init();
  void cleanup();

  /**
   * Tests for addRemoveSubsToJSON()
   */
  void testAddRemoveSubsToJSON();

  /**
   * Tests for saveSettingsToJSON()
   */
  void testSaveSettingsToJSON();

  /**
   * Tests for episodeActionListToJSON()
   */
  void testEpisodeActionListToJSON();

  /**
   * Tests for renameDeviceStringToJSON()
   */
  void testRenameDeviceStringToJSON();

  /**
   * Tests for deviceSynchronizationListsToJSON()
   */
  void testDeviceSynchronizationListsToJSON();
};

}

#endif // JSONCREATORTEST_H
