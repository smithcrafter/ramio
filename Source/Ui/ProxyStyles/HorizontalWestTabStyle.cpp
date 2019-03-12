/*
 * Copyright (C) 2016-2018 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio, a Qt-based casual C++ classes for quick development of a prototype application.
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

#include "HorizontalWestTabStyle.h"
// Qt5
#include <QtWidgets/QStyleOption>

namespace Ramio {

HorizontalWestTabStyle::HorizontalWestTabStyle(float kx, float ky)
	: QProxyStyle(Q_NULLPTR),
	  kx_(kx),
	  ky_(ky)
{
}

QSize HorizontalWestTabStyle::sizeFromContents(ContentsType type, const QStyleOption* option,
											   const QSize &size, const QWidget* widget) const
{
	QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
	if (type == QStyle::CT_TabBarTab)
	{
		s.transpose();
		s.setWidth(int(s.width()*kx_));
		s.setHeight(int(s.height()*ky_));
	}
	return s;
}

void HorizontalWestTabStyle::drawControl(ControlElement element, const QStyleOption* option,
										 QPainter* painter, const QWidget* widget) const
{
	if (element == CE_TabBarTabLabel)
		if (const auto* tab = qstyleoption_cast<const QStyleOptionTab*>(option))
		{
			QStyleOptionTab opt(*tab);
			opt.shape = QTabBar::RoundedSouth;
			QProxyStyle::drawControl(element, &opt, painter, widget);
			return;
		}
	QProxyStyle::drawControl(element, option, painter, widget);
}

} // Ramio::
