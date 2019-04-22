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

#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QSplitter>
#include <QtCore/QPointer>
// Ramio
#include <Global/Text.h>
#include <Gui/Global.h>
#include <Sets/UISets.h>
#include <Items/MetaItemSet.h>
#include <Items/ItemSet.h>

namespace Ramio {

template<class Contaiter, class T, class ContentItemWidget, class DetailItemWidget>
class ContentDetailWidget : public QWidget
{
public:
	ContentDetailWidget(const QString& windowTitle, const AbstractSet& set, const Meta::Description& metaDescription,
						const Contaiter* contaiter = Q_NULLPTR, QWidget* parent = Q_NULLPTR)
		: QWidget(parent), set_(set), metaDescription_(metaDescription), contaiter_(contaiter)
	{
		this->setWindowTitle(windowTitle);
		UI_CREATE_VLAUOUT(layout)
		UI_CREATE_TOOLBAR(BOLD(this->windowTitle()))
		UI_CREATE_TOOLBAR_STRECH
		tolbar_ = toolbar;

		splitter_ = new QSplitter();
		layout->addWidget(splitter_);
		splitter_->addWidget(contentItemWidget_ = new ContentItemWidget(set, metaDescription, splitter_));
		splitter_->addWidget(detailsWidget_ = new QWidget);

		QObject::connect(contentItemWidget_, &ContentItemWidget::selectedChanged, this, &ContentDetailWidget::onSelectedChanged);

		auto* detailsLayout = new QVBoxLayout(detailsWidget_);
		detailsLayout->addStretch();
		detailsLayout->addWidget(detailsLabel_ = new QLabel(tr("Элемент не выбран")), 1);
		detailsLayout->addLayout(detailsContentLayout_ = new QVBoxLayout(), 100);
		detailsLayout->addStretch();

		onSelectedChanged(Q_NULLPTR);
	}

	void loadSettings()
	{
		LOAD_WIDGET(splitter_)
		contentItemWidget_->loadSettings();
	}

	void saveSettings()
	{
		SAVE_WIDGET(splitter_)
		contentItemWidget_->saveSettings();
	}

	void onSelectedChanged(const Item* item)
	{
		if (detailItemWidget_)
			delete detailItemWidget_;

		item_ = item;
		detailsLabel_->setHidden(item_);

		if (item_)
			detailsContentLayout_->addWidget(detailItemWidget_ = new DetailItemWidget(*item, metaDescription_, contaiter_, this));
	}

	QToolBar* toolbar() {return tolbar_;}
	ContentItemWidget& contentItemWidget() {return *contentItemWidget_;}

private:
	const AbstractSet& set_;
	const Meta::Description& metaDescription_;
	const Contaiter* contaiter_;
	const Item* item_ = Q_NULLPTR;

	QToolBar* tolbar_;
	class QSplitter* splitter_;
	ContentItemWidget* contentItemWidget_;
	QVBoxLayout* detailsContentLayout_;
	QWidget* detailsWidget_;
	QLabel* detailsLabel_;
	QPointer<DetailItemWidget> detailItemWidget_ = Q_NULLPTR;
};

} // Ramio::
