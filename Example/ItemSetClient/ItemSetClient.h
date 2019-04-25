/*
 * Copyright (C) 2016-2018 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include <Network/TcpClient.h>
#include <Network/PacketBuilder.h>
#include <Protocol/ProtocolOperator.h>
#include <Items/FilterItemSet.h>
#include <QScopedPointer>
#include "../ItemSetServer/Tasks.h"
class LoginWidget;
class MainWidget;

class ItemSetClient : public QObject
{
public:
	ItemSetClient();
	~ItemSetClient() Q_DECL_OVERRIDE;

	void showLoginForm();
	void autoLogin();

	MetaTaskSet& tasks() {return tasks_;}
	Ramio::AbstractSet& arhiveTasks() {return arhiveTasks_;}

	void requestCreate(QString text, QColor color);
	void requestChangeCompleteStatus(const Task& task);
	void requestChangeArhiveStatus(const Task& task);
	void requestDelete(const Task& task);

private:
	void onLoginAccepted(const QString& login, const QString& password);
	void showMainWindow();

	ResDesc sendQuery(Ramio::Proto::QueryPacket& packet);

	void onAnswerReceived(Ramio::Proto::Queries query, const Ramio::Proto::AnswerPacket& packet,
						  const Ramio::Proto::XmlDocument& doc, const Ramio::ConnectionInfo& from);
	void onEventReceived(Ramio::Proto::Events event, const Ramio::Proto::EventPacket& packet,
						 const Ramio::Proto::XmlDocument& doc, const Ramio::ConnectionInfo& from);

private:
	Ramio::TcpClient client_;
	Ramio::PacketBuilder packetBuilder_;
	Ramio::ProtocolOperator protocolOperator_;

	MetaTaskSet tasks_;
	Ramio::FilterItemSet<Task> arhiveTasks_;

	qint64 pid_ = 0;
	QScopedPointer<LoginWidget> loginWidget_;
	QScopedPointer<MainWidget> mainWidget_;
};
