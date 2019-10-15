/*
 * Copyright (C) 2016-2019 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio Examples, a Qt-based casual C++ classes for quick application writing.
 *
 * Ramio is free software; you can redistribute it and/or modify it under the terms of the
 * GNU Lesser General Public License as published by the Free Software Foundation;
 * either version 3 of the License, or (at your option) any later version.
 *
 * Ramio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Ramio; see the file LICENSE. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <Database/Database.h>
#include <Network/TcpServer.h>
#include <Network/PacketBuilder.h>
#include <Protocol/ProtocolOperator.h>
#include <Items/ItemWatcher.h>
#include <Users.h>
#include <Tasks.h>

class ItemSetServer : public QObject
{
public:
	ItemSetServer();

	bool openDatabase();
	bool startListening();

	MetaUserSet& users() {return users_;}
	MetaTaskSet& tasks() {return tasks_;}

	void addUser(User& user);

	Ramio::ItemWatcher& currentUser() {return currentUser_;}

private:
	void onQueryReceived(Ramio::Proto::Queries query, const Ramio::Proto::QueryPacket& packet, const Ramio::ConnectionInfo& client);
	void onClientDisconnected(const Ramio::ConnectionInfo& client);
	void sendAnswer(Ramio::Proto::Queries query, const Ramio::Proto::AnswerPacket& packet, const Ramio::ConnectionInfo& to);
	void sendEvent(Ramio::Proto::Events query, const Ramio::Proto::EventPacket& packet, const Ramio::ConnectionInfo& to);

	void doOnLogin();
	void doOnLogout();

private:
	Ramio::Database database_;
	MetaUserSet users_;
	MetaTaskSet tasks_;
	Ramio::TcpServer server_;
	Ramio::PacketBuilder packetBuilder_;
	Ramio::ProtocolOperator protocolOperator_;

	Ramio::ItemWatcher currentUser_;
	Ramio::ConnectionInfo currentConnection_;

	qint64 epid_ = 0;
};
