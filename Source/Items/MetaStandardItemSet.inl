#include "MetaStandardItemSet.h"

namespace Ramio {

template<typename METAITEM, typename METASTRUCTDATA, bool CACHEDID, bool CACHEDUUID>
MetaStandardItemSet<METAITEM, METASTRUCTDATA, CACHEDID, CACHEDUUID>::MetaStandardItemSet
		(QString setName, QString itemName, std::shared_ptr<Meta::TypeDescription> typeDescription, QObject* parent)
	: MetaItemSet<METAITEM, METASTRUCTDATA, CACHEDID>(setName, itemName, parent)
{
	AbstractMetaSet::meta_.typeDescription = std::move(typeDescription);
}

} // Ramio::
