# Ramio - C++/Qt Library [0.1.5e]

Набор шаблонов и классов для создания объектов с мета-описанием во времени выполнения.

Библиотека содержит базовые возможности:
+ создание мета-описания через макросы в теле элемента (структуры/класса);
+ контейнер элементов, фильтрующий контейнер;
+ qt-сигналы добавления/изменения/удаления элементов внутри контейнера;
+ сериализация/десериализация;
+ взаимодействие с БД;
+ интерфейс отображения таблиц;
+ формы редактирования элементов по мета-информации;
+ взаимодействие по сети.

**Внимание! Разрабатывается для личных целей, сохранность интерфейсов не гарантируется.**

Краткий пример определения:

	struct NoteRecord : Ramio::MetaItemData
	{
	  RMetaString title;
	  RMetaString text;
	  RMetaDateTime time;
	  RMetaPKey sectionId;

	  RMETA_DATA_BEGIN
	  RMETA_DATA_FIELD(title, String, "Заголовок")
	  RMETA_DATA_FIELD(text, String, "Текст")
	  RMETA_DATA_FIELD(time, DateTime, "Время")
	  RMETA_DATA_FKEY_ID(sectionId, "Раздел")
	  RMETA_DATA_END
	};

	GENERATE_METACLASS(Note, NoteRecord)
	GENERATE_METASET(NoteSet, Note, NoteRecord)

После чего доступны сериализация/дересериализация списка объектов,
сохранение/загрузка из БД (+подготовка таблиц БД на основании метаинформации),
виджеты отображения и редактирования, модели для таблиц, передача по сети.

Примеры использования:

	NoteSet set;

	// Инициализация таблиц в бд
	database.initTable(set.meta());

	// Загрузка из бд.
	database.selectMetaItemDataSet(set);

	// Создание элемента
	NoteRecord rec{...}
	if (database.insertMetaItemData(rec, set.meta()).noError())
	  set.addItem(rec);

	// Сохранение в XML
	QDomElement de;
	set.serialize(de);

	// Использование в моделях для отображения
	auto* view = new QTableView;
	auto* model = new Ramio::MetaItemsModel(set, set.meta());
	view->setModel(model);
