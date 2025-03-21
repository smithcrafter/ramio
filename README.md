# Ramio is RAM object with Input-Output instructions
**C++/Qt Library [0.1.9]**

A set of templates and classes for creating objects with a meta description at runtime.

The library contains basic features:
+ creation of a meta-description through macros in the body of an element (structure/class);
+ container of elements, filtering container, uniting;
+ qt-signals for adding/changing/deleting elements inside the container;
+ serialization/deserialization;
+ interaction with the database;
+ interface for displaying tables;
+ forms for editing elements by meta-information;
+ network interaction.

**Attention! It is developed for personal purposes, the safety of interfaces is not guaranteed.**

Brief definition example:

	RDECL_CONTAINER_CLASS_STRUCT(NoteSet, Note, NoteRecord)

	struct NoteRecord : Ramio::MetaItemData
	{
	  RMString title;
	  RMString text;
	  RMDateTime time;
	  RMPKey sectionId;

	  RMETA_DATA_BEGIN
	  RMETA_DATA_FIELD(title, String, "Заголовок")
	  RMETA_DATA_FIELD(text, String, "Текст")
	  RMETA_DATA_FIELD(time, DateTime, "Время")
	  RMETA_DATA_FKEY_ID(sectionId, "Раздел")
	  RMETA_DATA_END
	};

	RGEN_METACLASS(Note)

	RGEN_METASET(NoteSet, "Notes", "Note")

After that, the following are available: serialization / deserialization of the list of objects, saving / loading from the database (as well as preparing database tables based on meta-information), display and editing widgets, models for tables, network transmission.

Examples of using:

	NoteSet set;

	// Database table initialization
	database.initTable(set.meta());

	// Loading from database
	database.selectMetaItemDataSet(set);

	// Create an element
	NoteRecord rec{...}
	if (database.insertMetaItemData(rec, set.meta()).noError())
	  set.addItem(rec);

	// Saving to XML
	QDomElement de;
	set.serialize(de);

	// Use in models for display
	auto* view = new QTableView;
	auto* model = new Ramio::MetaItemsModel(set);
	view->setModel(model);
