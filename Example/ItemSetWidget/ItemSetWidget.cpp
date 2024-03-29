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

#include "ItemSetWidget.h"
#include "Notes.h"
#include "Sections.h"
// Ramio
#include <Widgets/ContentWidget.h>
#include <Widgets/TableWidget.h>
#include <Widgets/ItemDetailWidget.h>
#include <Widgets/ItemEditWidget.h>
#include <Gui/Global.h>
#include <Sets/UISets.h>
// Qt
#include <QtWidgets/QAction>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QHeaderView>
#include <QtXml/QDomDocument>
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QStringBuilder>

static RMPKey newNoteId = 0;
static RMPKey newSectionId = 0;
using SectionsContentWidget = Ramio::ContentWidget<Section, Ramio::TableWidget, Ramio::ItemDetailWidget>;
using NotesContentWidget = Ramio::ContentWidget<Note, Ramio::TableWidget, Ramio::ItemDetailWidget>;

ItemSetWidget::ItemSetWidget(QWidget *parent)
	: QWidget(parent),
	  sectoins_(new MetaSectionSet(this)),
	  notes_(new MetaNoteSet(this))
{
	notes_->setRelationSet(QStringLiteral("sectionId"), sectoins_);

	this->setWindowTitle(tr("Пример импользования айтемов"));
	auto* layout = new QHBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);

	layout->addWidget(tabs_ = new QTabWidget(this));
	tabs_->addTab(sectoinsWidget_ = new SectionsContentWidget(tr("Разделы"), *sectoins_, tabs_), tr("Разделы"));

	auto* toolbar = static_cast<SectionsContentWidget*>(sectoinsWidget_)->toolbar();
	toolbar->addAction(tr("Добавить"), this, &ItemSetWidget::showNewSectionDialog);
	toolbar->addAction(tr("Удалить"), this, &ItemSetWidget::removeSelectedSection);

	tabs_->addTab(notesWidget_ = new NotesContentWidget(tr("Заметки"), *notes_, tabs_), tr("Заметки"));
	static_cast<NotesContentWidget*>(notesWidget_)->contentItemWidget()
			.setColumns({"type", "title", "text", "time", "sectionId"});

	toolbar = static_cast<NotesContentWidget*>(notesWidget_)->toolbar();
	toolbar->addAction(tr("Обновить"), this, &ItemSetWidget::reloadNotes);
	toolbar->addAction(tr("Добавить"), this, &ItemSetWidget::showNewNoteDialog);
	toolbar->addAction(tr("Случайный"), this, &ItemSetWidget::addRandomNote);
	toolbar->addAction(tr("Изменить"), this, &ItemSetWidget::showChangeSelectedNoteDialog);
	toolbar->addAction(tr("Удалить"), this, &ItemSetWidget::removeSelectedNote);
	toolbar->addAction(tr("Очистить"), this, &ItemSetWidget::clearNotes);

	loadSettings();
	loadFromFile();
}

ItemSetWidget::~ItemSetWidget()
{
	saveSettings();
	saveToFile();
}

void ItemSetWidget::loadSettings()
{
	LOAD_SETTINGS(static_cast<NotesContentWidget*>(sectoinsWidget_));
	LOAD_SETTINGS(static_cast<NotesContentWidget*>(notesWidget_));
	LOAD_GEOMETRY(this);
}

void ItemSetWidget::saveSettings()
{
	SAVE_GEOMETRY(this);
	SAVE_SETTINGS(static_cast<NotesContentWidget*>(sectoinsWidget_));
	SAVE_SETTINGS(static_cast<NotesContentWidget*>(notesWidget_));
}

void ItemSetWidget::loadFromFile()
{
	QFile file(QCoreApplication::applicationDirPath() % QDir::separator() % "notes.xml");
	if (file.open(QIODevice::ReadOnly))
	{
		QDomDocument doc;
		if (doc.setContent(file.readAll()))
		{
			QDomElement deContent = doc.firstChildElement(QStringLiteral("Content"));
			if (!deContent.isNull())
			{
				QDomElement deSections = deContent.firstChildElement(sectoins_->meta().setName);
				if (!deSections.isNull())
				{
					sectoins_->deserialize(deSections);
					for (const auto* item: sectoins_->items())
						if (item->id() >= newSectionId)
							newSectionId = item->id()+1;
				}
				QDomElement deNotes = deContent.firstChildElement(notes_->meta().setName);
				if (!deNotes.isNull())
				{
					notes_->deserialize(deNotes);
					for (const auto* item: notes_->items())
						if (item->id() >= newNoteId)
							newNoteId = item->id()+1;
				}
			}
		}
		file.close();
	}
}

void ItemSetWidget::saveToFile()
{
	QFile file(QCoreApplication::applicationDirPath() % QDir::separator() % "notes.xml");
	if (file.open(QIODevice::WriteOnly))
	{
		QDomDocument doc;
		QDomElement deContent = doc.createElement(QStringLiteral("Content"));
		doc.appendChild(deContent);
		QDomElement deNotes = doc.createElement(notes_->meta().setName);
		deContent.appendChild(deNotes);
		notes_->serialize(deNotes);
		QDomElement deSections = doc.createElement(sectoins_->meta().setName);
		deContent.appendChild(deSections);
		sectoins_->serialize(deSections);
		file.write(doc.toByteArray());
		file.close();
	}
}

void ItemSetWidget::reloadNotes()
{
	notes_->refresh();
}

void ItemSetWidget::showNewSectionDialog()
{
	auto* widget = new Ramio::ItemEditWidget(*sectoins_, Q_NULLPTR, this);
	connect(widget, &Ramio::ItemEditWidget::accepted, this, &ItemSetWidget::onNewSectionAccepted);
	connect(widget, &Ramio::ItemEditWidget::canceled, widget, &QWidget::close);
	SHOW_MODAL_DIALOG_WIDGET(widget);
}

void ItemSetWidget::showNewNoteDialog()
{
	auto* widget = new Ramio::ItemEditWidget(*notes_, Q_NULLPTR, this);
	connect(widget, &Ramio::ItemEditWidget::accepted, this, &ItemSetWidget::onNewNoteAccepted);
	connect(widget, &Ramio::ItemEditWidget::canceled, widget, &QWidget::close);
	SHOW_MODAL_DIALOG_WIDGET(widget);
}

void ItemSetWidget::onNewSectionAccepted(Ramio::Item *newItem)
{
	newItem->data().id = ++newSectionId;
	sectoins_->insertItem(static_cast<Section*>(newItem));
	if (auto* widget = static_cast<QWidget*>(sender()))
		widget->close();
}

void ItemSetWidget::onNewNoteAccepted(Ramio::Item* newItem)
{
	newItem->data().id = ++newNoteId;
	notes_->insertItem(static_cast<Note*>(newItem));
	if (auto* widget = static_cast<QWidget*>(sender()))
		widget->close();
}

void ItemSetWidget::onChangeNoteAccepted(Ramio::Item* changedItem)
{
	if (auto* widget = static_cast<Ramio::ItemEditWidget*>(sender()))
	{
		if (const auto* originItem = widget->originItem())
			static_cast<Note*>(const_cast<Ramio::Item*>(originItem))->updateData(static_cast<Note*>(changedItem)->data());
		widget->close();
	}
	delete changedItem;
}

void ItemSetWidget::addRandomNote()
{
	NoteRecord rec (tr("Заголовок ") % QString::number(++newNoteId), tr("Текст"), QDateTime::currentDateTime());
	rec.id = newNoteId;
	rec.uuid = QUuid::createUuid();
	rec.type = notes_->meta().typeDescription->supportedTypes()[std::rand()%notes_->meta().typeDescription->supportedTypes().count()];
	rec.sectionId = std::rand() % newSectionId+1;
	notes_->addItem(rec);
}

void ItemSetWidget::showChangeSelectedNoteDialog()
{
	if (auto* item = static_cast<NotesContentWidget*>(notesWidget_)->contentItemWidget().currentItem())
	{
		auto* widget = new Ramio::ItemEditWidget(*notes_, item,  this);
		connect(widget, &Ramio::ItemEditWidget::accepted, this, &ItemSetWidget::onChangeNoteAccepted);
		connect(widget, &Ramio::ItemEditWidget::canceled, widget, &QWidget::close);
		SHOW_MODAL_DIALOG_WIDGET(widget);
	}
}

void ItemSetWidget::removeSelectedSection()
{
	if (auto* item = static_cast<SectionsContentWidget*>(sectoinsWidget_)->contentItemWidget().currentItem())
		delete item;
}

void ItemSetWidget::removeSelectedNote()
{
	if (auto* item = static_cast<NotesContentWidget*>(notesWidget_)->contentItemWidget().currentItem())
		delete item;
}

void ItemSetWidget::clearNotes()
{
	notes_->clear();
}
