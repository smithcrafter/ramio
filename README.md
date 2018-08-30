# Ramio - C++/Qt Library [0.1.0d]

Набор классов для создания мета объектов и вспомогательные элементы для 
постоения приложений.
**Разрабатывается для личных целей, сохранность интерфейсов не гарантируется.**

Краткий пример использования:

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
    
    GENERATE_HEADER_CLASS(Note, NoteRecord)
    GENERATE_HEADER_CLASS_METASET(MetaNoteSet, Note, NoteRecord)

После чего доступны сериализация, дересериализация списков объектов, 
сохранение/загрузка из БД (+подготовка таблиц в бд на основании метаинформации), 
виджеты отображения и редактирования, модели для таблиц, передача по сети.
