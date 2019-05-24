# Ramio - C++/Qt Library [0.1.2e]

Набор классов для создания мета объектов и вспомогательные элементы для постоения приложений.

**Внимание! Разрабатывается для личных целей, сохранность интерфейсов не гарантируется.**

Краткий пример определения:

	struct NoteRecord : Ramio::MetaItemData
	{
	  RMetaString title;
	  RMetaString text;
	  RMetaDateTime time;
	  RMetaPKey sectionId;

	  RMETA_OBJECT_START(MetaItemData)
	  RMETA_OBJECT_FIELD(title, String, "Title", "Заголовок", Field)
	  RMETA_OBJECT_FIELD(text, String, "Text", "Текст", Field)
	  RMETA_OBJECT_FIELD(time, DateTime, "Time", "Время", Field)
	  RMETA_OBJECT_FIELD(sectionId, PKey, "SectionId", "Раздел", FKey)
	  RMETA_OBJECT_END

	  NoteRecord() = default;
	};

	GENERATE_CLASS(Note, NoteRecord)
	GENERATE_CLASS_METASET(MetaNoteSet, Note, NoteRecord)

После чего доступны сериализация, дересериализация списка объектов,
сохранение/загрузка из БД (+подготовка таблиц БД на основании метаинформации),
виджеты отображения и редактирования, модели для таблиц, передача по сети.

Примеры использования:

	MetaNoteSet set;

	// Инициализация таблиц в бд
	database.initTable(set.meta());

	// Загрузка из бд.
	database.selectMetaItemData(set);

	// Создание элемента
	NoteRecord rec{...}
	if (database.saveMetaItemData(rec, set.meta()).noError())
	  set.addItem(rec);

	// Сохранение в XML
	QDomElement de;
	set.serialize(de);

	// Использование в моделях для отображения
	auto* view = new QTableView;
	auto* model = new Ramio::MetaItemsModel(set, set.meta());
	view->setModel(model);
