/*
 * Copyright (C) 2016-2021 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "LoginWidget.h"
#include <Sets/Config.h>
#include <Sets/UISets.h>
#include <Global/Text.h>
#include <Gui/Global.h>
// Qt5
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>

LoginWidget::LoginWidget(const QString& title, QWidget* parent)
	: QWidget(parent)
{
	this->setWindowTitle(title);
	UI_CREATE_GLAYOUT(layout)
	layout->addWidget(new QLabel, 0, 0, 3, 1);
	layout->addWidget(new QLabel(H1(title)), 0, 1, 1, 3);
	layout->addWidget(new QLabel(tr("Пользователь")), 1, 1);
	layout->addWidget(new QLabel(tr("Пароль")), 2, 1);
	layout->addWidget(loginEdit_ = new QLineEdit(), 1, 2);
	layout->addWidget(passEdit_ = new QLineEdit(), 2, 2);
	passEdit_->setEchoMode(QLineEdit::PasswordEchoOnEdit);
	QPushButton* button;
	layout->addWidget(button = new QPushButton(tr("Вход")), 1, 3, 2, 1);
	connect(button, &QPushButton::clicked, this, &LoginWidget::checkLogin);
	button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	loginEdit_->setFocus();
}

void LoginWidget::autoLogin()
{
	loginEdit_->setText("user1");
	passEdit_->setText("1");
	checkLogin();
}

void LoginWidget::checkLogin()
{
	if (loginEdit_->text().isEmpty())
		loginEdit_->setFocus();
	else if (passEdit_->text().isEmpty())
		passEdit_->setFocus();
	else
		emit accepted(loginEdit_->text(), passEdit_->text());
}
