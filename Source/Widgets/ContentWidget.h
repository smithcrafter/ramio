/*
 * Copyright (C) 2016-2021 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

template<class ITEM, class TableWidget, class DetailWidget>
class ContentWidget : public QWidget
{
public:
	ContentWidget(const QString& windowTitle, const AbstractMetaSet& set, QWidget* parent = Q_NULLPTR)
		: ContentWidget(windowTitle, *set.aSet(), set.meta(), parent) {}

	ContentWidget(const QString& windowTitle, const AbstractListSet& set, const Meta::Description& metaDescription,
						QWidget* parent = Q_NULLPTR)
		: QWidget(parent), set_(set), metaDescription_(metaDescription)
	{
		this->setWindowTitle(windowTitle);
		UI_CREATE_VLAYOUT(layout)
		UI_CREATE_TOOLBAR(layout, BOLD(this->windowTitle()))
		UI_CREATE_TOOLBAR_STRECH(toolbar)
		tolbar_ = toolbar;

		splitter_ = new QSplitter();
		layout->addWidget(splitter_);
		splitter_->addWidget(contentItemWidget_ = new TableWidget(set, metaDescription, splitter_));
		splitter_->addWidget(detailsWidget_ = new QWidget);

		QObject::connect(contentItemWidget_, &TableWidget::selectedChanged, this, &ContentWidget::onSelectedChanged);

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
		if (detailWidget_)
		{
			detailWidget_->setHidden(true);
			detailsContentLayout_->removeWidget(detailWidget_.data());
			detailWidget_->deleteLater();
			detailWidget_ = Q_NULLPTR;
		}

		item_ = static_cast<const ITEM*>(item);
		detailsLabel_->setHidden(item_);

		if (item_)
			detailsContentLayout_->addWidget(detailWidget_ = new DetailWidget(*item_, metaDescription_, detailsWidget_));
	}

	QToolBar* toolbar() {return tolbar_;}
	TableWidget& contentItemWidget() {return *contentItemWidget_;}

private:
	const AbstractListSet& set_;
	const Meta::Description& metaDescription_;
	const ITEM* item_ = Q_NULLPTR;

	QToolBar* tolbar_;
	QSplitter* splitter_;
	TableWidget* contentItemWidget_;
	QVBoxLayout* detailsContentLayout_;
	QWidget* detailsWidget_;
	QLabel* detailsLabel_;
	QPointer<DetailWidget> detailWidget_ = Q_NULLPTR;
};

} // Ramio::
