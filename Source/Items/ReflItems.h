// for test

#pragma once

#include "Item.h"
#include "StructItem.h"
#include "AbstractListSet.h"
#include "MetaDescription.h"

namespace Ramio {

template<int COUNT>
struct ReflData : public ItemData
{
	char dsubtata[COUNT] ;
};

template<int COUNT>
class ReflItem : public StructItem<ReflData<COUNT>>
{
	typedef ReflData<COUNT> Data;
	typedef StructItem<ReflData<COUNT>> Base;
public:
	ReflItem() : Base() {}
	ReflItem(const Data& data) : Base(data) {}
};

class ReflSet : public AbstractListSet
{
public:
	ReflSet(const Meta::Description& meta, QObject* parent = Q_NULLPTR);

	const Meta::Description& meta() const {return meta_;}

	virtual Item* createItem() const;
	virtual Item* createItem(const ItemData& data) const {Q_UNUSED(data); return Q_NULLPTR;}
	virtual Item* createItem(ItemData&& data) const {Q_UNUSED(data); return Q_NULLPTR;}
	virtual AbstractListSet* createTemporaryItemSet(QObject* parent = Q_NULLPTR) const {Q_UNUSED(parent); return Q_NULLPTR;}

private:
	QList<Item*> items_;
	Meta::Description meta_;
};

} // Ramio::
