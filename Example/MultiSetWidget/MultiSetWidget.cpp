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

#include "MultiSetWidget.h"
// Ramio
#include <Widgets/ContentWidget.h>
#include <Widgets/ItemDetailWidget.h>
#include <Widgets/TableWidget.h>
#include <Log/Log.h>
// Qt
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>

static RMPKey newNoteId = 0;
using NotesContentWidget = Ramio::ContentWidget<Note, Ramio::TableWidget, Ramio::ItemDetailWidget>;

MultiSetWidget::MultiSetWidget(QWidget* parent)
	: QWidget(parent)
{
	this->setWindowTitle(tr("Пример импользования наборов"));
	auto* layout = new QHBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);

	layout->addWidget(tabs_ = new QTabWidget(this));


	for (int i = 0; i < 4; i++)
	{
		sets_.append(new MetaNoteSet(this));
		auto w = new NotesContentWidget(tr("Заметки %1").arg(i+1), *sets_[i], tabs_);
		notesWidgets_.append(w);
		tabs_->addTab(w, tr("Заметки %1").arg(i+1));
		w->contentItemWidget().setColumns({"id", "type", "title", "text", "time"});
		w->loadSettings();
		w->toolbar()->addAction(tr("Случайный"), this, &MultiSetWidget::addRandomNote);
		w->toolbar()->addAction(tr("Удалить"), this, &MultiSetWidget::removeSelectedNote);
	}

	mergerItemSet_ = new Ramio::MergerItemSet<Note>(*sets_[0], *sets_[1], this);
	auto mergerWidget = new NotesContentWidget(tr("Заметки 1and2"), *mergerItemSet_, sets_[0]->meta(), tabs_);
	notesWidgets_.append(mergerWidget);
	tabs_->addTab(mergerWidget, tr("Заметки 1and2"));
	mergerWidget->loadSettings();
	mergerWidget->toolbar()->addAction(tr("Удалить"), this, &MultiSetWidget::removeSelectedNote);

	multiMergerMetaItemSet_ = new Ramio::MultiMergerMetaItemSet<Note>(QList<const Ramio::AbstractListSet*>()<<sets_[1]<<sets_[2]<<sets_[3], this);
	auto multiMergerWidget = new NotesContentWidget(tr("Заметки 2and3and4"), *multiMergerMetaItemSet_, sets_[0]->meta(), tabs_);
	notesWidgets_.append(multiMergerWidget);
	tabs_->addTab(multiMergerWidget, tr("Заметки 2and3and4"));
	multiMergerWidget->loadSettings();
	multiMergerWidget->toolbar()->addAction(tr("Удалить"), this, &MultiSetWidget::removeSelectedNote);
}

MultiSetWidget::~MultiSetWidget()
{
	delete mergerItemSet_;
	delete multiMergerMetaItemSet_;
}

void MultiSetWidget::addRandomNote()
{
	auto index = tabs_->currentIndex();
	if (index >= 4)
		return;

	NoteRecord rec;
	rec.title = tr("Заголовок ") % QString::number(++newNoteId);
	rec.text = tr("Текст");
	rec.time =  QDateTime::currentDateTime();
	rec.id = newNoteId;
	rec.uuid = QUuid::createUuid();
	rec.type = std::rand()%10;
	sets_[index]->addItem(rec);
}

void MultiSetWidget::removeSelectedNote()
{
	if (auto* item = static_cast<NotesContentWidget*>(notesWidgets_[tabs_->currentIndex()])->contentItemWidget().currentItem())
		delete item;
}
