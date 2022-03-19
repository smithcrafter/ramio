// for test

#include "ReflItems.h"

namespace Ramio {

ReflSet::ReflSet(const Meta::Description& meta, QObject* parent)
	: AbstractListSet(items_, parent),
	  meta_(meta)
{
}

Item* ReflSet::createItem() const
{
	Item* item = Q_NULLPTR;
	if (meta_.size<=8)
		item =  new ReflItem<8>();
	else if (meta_.size<=32)
		item =  new ReflItem<32>();
	else if (meta_.size<=128)
		item =  new ReflItem<128>();
	else if (meta_.size<=1024)
		item =  new ReflItem<1024>();
	else
		return Q_NULLPTR;
	auto& data = item->data();
	for (auto pr: meta_.properties)
	{
		if (pr.type == Meta::Type::PKey)
			CAST_DATAREL_TO_TYPEREL(RMPKey) = 0;
		if (pr.type == Meta::Type::Uuid)
			CAST_DATAREL_TO_TYPEREL(RMUuid) = QUuid();
		if (pr.type == Meta::Type::Long)
			CAST_DATAREL_TO_TYPEREL(RMLong) = 0;
	}

	return item;
}

} // Ramio::
