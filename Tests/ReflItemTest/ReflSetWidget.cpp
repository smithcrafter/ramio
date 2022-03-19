#include "ReflSetWidget.h"
#include <Items/MetaItemSerialization.h>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTabWidget>
#include <Widgets/TableWidget.h>
#include <Gui/Global.h>
#include <QtXml/QDomElement>

ReflSetWidget::ReflSetWidget(QWidget* parent)
	: QWidget(parent),
	  rset(set.meta())
{
	this->setWindowTitle(tr("Пример импользования наборов"));
	UI_CREATE_HLAYOUT_ZERO_MARGINSPACING(layout);
	UI_CREATE_TOOLBAR(layout, "Проверка копии сета");
	toolbar->addAction("Добавить случайный", this, &ReflSetWidget::addRandom);

	layout->addWidget(tabs_ = new QTabWidget(this));
	tabs_->addTab(new Ramio::TableWidget(set), "Базовый сет");
	tabs_->addTab(new Ramio::TableWidget(rset, rset.meta()), "Рефл сет");


	connect(&set, &TestSet::added, this, [this](const Ramio::Item& item){
		QDomDocument doc;
		QDomElement de = doc.createElement(set.meta().itemName);
		Ramio::Serialization::serialize(set.meta(), item.data(), de);
		auto ritem = rset.createItem();
		Ramio::Serialization::deserialize(rset.meta(), ritem->data(), de);
		rset.insertItem(*ritem);
	});

}

void ReflSetWidget::addRandom()
{
	auto item = set.createItem();
	item->data().value = std::rand();
	set.insertItem(item);
}
