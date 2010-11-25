/*
 * EpisodeList.cpp
 *
 *  Created on: Nov 25, 2010
 *      Author: IXI
 */

#include "EpisodeList.h"

namespace mygpo {

EpisodeList::EpisodeList(QNetworkReply* reply, QObject* parent) {
	this->reply = reply;
}

EpisodeList::EpisodeList(const EpisodeList& episodeList) {
	this-> reply = episodeList.reply;
}

EpisodeList::~EpisodeList() {
	// TODO Auto-generated destructor stub
}

}
