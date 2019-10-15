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

#include <QtWidgets/QWidget>
namespace Ramio {class Item;}
class MetaNoteSet;
class MetaSectionSet;
class QTabWidget;

class ItemSetWidget : public QWidget
{
public:
	ItemSetWidget(QWidget* parent = Q_NULLPTR);
	~ItemSetWidget() Q_DECL_OVERRIDE;

	void loadSettings();
	void saveSettings();

	void loadFromFile();
	void saveToFile();

	void reloadNotes();
	void showNewSectionDialog();
	void showNewNoteDialog();
	void addRandomNote();
	void showChangeSelectedNoteDialog();
	void removeSelectedSection();
	void removeSelectedNote();
	void clearNotes();

private:
	void onNewSectionAccepted(Ramio::Item* newItem);
	void onNewNoteAccepted(Ramio::Item* newItem);
	void onChangeNoteAccepted(Ramio::Item* changedItem);

private:
	MetaSectionSet* sectoins_;
	MetaNoteSet* notes_;
	QTabWidget* tabs_;
	QWidget* sectoinsWidget_;
	QWidget* notesWidget_;
};
