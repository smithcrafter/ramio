## 0.1.5d4 TestItems [14.05.2020]
- KeyValue тестовые структуры для проверки размера сжатого класса

## 0.1.5d3 RMETA_CLASS_PROPERTY [14.05.2020]
- Макрос RMETA_CLASS_PROPERTY для описания полей данных внутри функции updateMetaDescription
- Фикс вызова registerMetaFields для структур, не унаследованных от MetaItemData
- Временно отключена функция createMetaItemData

## 0.1.5d2 Сохранение первичного ключа без инкремента [09.05.2020]
- Появилась возможность сохранять первичный ключ (пока только для типа PKey)
- Структура DatabaseSpecial в формировании таблицы может быть изменена извне, предосавлен доступ
- RMetaPKey стал знаковым типом, но отрицательная часть не планируется использовать в БД

## 0.1.5d1 Readme.md [28.04.2020]
- Обновлено описание

## 0.1.5d RMETA_DATA_* [20.04.2020]
- Переименованы макросы RMETA_OBJECT_* в RMETA_DATA_*

## 0.1.5c3 Example fix [19.04.2020]
- Сборка примеров, после изменения макросов
- Новые констукторы MetaItemSet без генерации мета информации
- Подготовка к генерации мета информации в классе Item

## 0.1.5c2 SqlQuery uuid condition [18.04.2020]
- Формирование SQL запросов с условием по QUuid - SqlQuery::setConditionUuid

## 0.1.5c1 ELOG [17.04.2020]
- Error log macros для вывода ошибок
- Подправлен вывод класса взаимодействия с БД
- Вывод sql запросов опционально, от флагов запуска

## 0.1.5c Новое поле в метаописании [16.04.2020]
- Планируется сделать вторичный ключ на идентификатор, отличный от int64 id, описание будет хранить имя поля
- Макрос RMETA_OBJECT_PROPERTY принимает на один параметр больше
- Новые макросы RMETA_OBJECT_FKEY_ID, RMETA_OBJECT_FKEY_ID_C, RMETA_OBJECT_VALUE

## 0.1.5b2 Фикс сборки под mingw [30.03.2020]
- Подправлен конструктор FilterItemSet для сборки под windows

## 0.1.5b1 Макрос цветного маркера CHCOLOR [27.03.2020]
- Добавлен макрос цветного квадрата CHCOLOR
- QtWidgetsDeclaration дополнен включением QPointer

## 0.1.5b KeyValueRecord перемещён в другой проект [25.03.2020]
- Удалён класс KeyValueRecord, отвечающий за сериализацию ключ/значение в строку и обратно

## 0.1.5a10 WHITETEXT [15.03.2020]
- Новый макрос для белого текста WHITETEXT

## 0.1.5a9 ModelFilterWidget [12.03.2020]
- Установка фильтра в классе ModelFilterWidget
- Получение доступа к ModelFilterWidget из TableWidget

## 0.1.5a8 saveWidgetValue/loadWidgetValue [02.03.2020]
- Сохранение дополнительных полей в параметрах виджета

## 0.1.5a7 Fix nullptr set [28.02.2020]
- Фиск отсутвия проверки в APGetDataSet при возникновении ошибки и отсутвию набора

## 0.1.5a6 Отлючил вызов функции по адресу в DEBUG сборке [27.02.2020]
- Вызов функции по адресу неверно вычислял this в отладочной сборке, отлючён до поиска верного решения

## 0.1.5a5 Более точный поиск поля [11.02.2020]
- Поиск индекса поля fieldDiff по типу переменной и имени
- Поля состояния и флагов в структуре MetaStandardItemData теперь переменные, а не поля для сохранения
- Не шаблоная функция valueToString

## 0.1.5a4 DataFunctionPrt часть MetaItemData [10.02.2020]
- Объединение DataFunctionPrt стало частью класса MetaItemData
- Делать мета-описание функции можно только наследникам MetaItemData вновь
- Вызов функции по метаописанию перенесён в класс MetaItemData
- Некоторые уточнения для сравнения, прохождение теста востановлено

## 0.1.5a3 Фикс вызова макроса CAST_CONST_DATAREL_TO_TYPEREL [09.02.2020]
- В макром CAST_CONST_DATAREL_TO_TYPEREL передаётся Ramio::Data а не Ramio::MetaItemData
- Ещё производится работа с DataFunctionPrt().call при вызове функции по указателю (падает в debug)

## 0.1.5a2 Макросы StandardItem [08.02.2020]
- Добавлен макрос GENERATE_HEADER_STANDARDSET_START_WITHCACHE аналогично GENERATE_HEADER_METASET_START_WITHCACHE
- Фикс макроса GENERATE_STANDARDCLASS

## 0.1.5a1 Перемещения StandardItem [02.02.2020]
- Шаблоны StandardItem и MetaStandardItemSet вынесены в отдельный заголовочный файл
- Макрос GENERATE_METABASESET переименован в GENERATE_STANDARDSET

## 0.1.5a RMETA_OBJECT_FUNCTION только для MetaItemData [31.01.2020]
- Описание функция только для наследников класса MetaItemData

## 0.1.5 Глобальные переименования [30.01.2020]
- Класс BaseItem переименован в StandrdItem, MetaBaseItemSet в MetaStandardItemSet, MetaBaseItemData в MetaStandardItemData
- Макросы BASECLASS переименованы в STANDARDCLASS
- Макросы GENERATE_CLASS переименованы в GENERATE_METACLASS
- Структура ItemData разбита на 2 стуктуры, констукторы вынесены BaseItemData
- Вычисление смещения поля считается от указателя на Ramio::Data, а не от наследованной стуктуры
- Подправлены примеры, проекты
TODO
Прорабатывается вариант использования метаописания так же и в классе Item.
Из иерархии ItemData убираются виртуальные методы для экономии памяти (дестуктор наследованной стуктуры вызовется из StructItem).
В планах сделать набор элементов на непрерывной памяти, а не через указатели.

## 0.1.4d7 ConnectionState && Log::Notices [29.01.2020]
- Добавлены функциия состояния сокета в классы TCP соединений
- Notices доступен и для консольной сборки, добавлена виртуальная функция добавления лога для изменения обработки

## 0.1.4d6 Разделения макросов [28.01.2020]
- Макросы создания MetaBaseItem и MetaItem разделены в разные файлы
- Незначительные правки по пространствам имён

## 0.1.4d5 ItemChanger для Item [24.01.2020]
- Структура ItemChanger, для изменения данных, перемещена со StructItem до базового класса Item

## 0.1.4d4 FilterMetaItemSet2 && Description [23.01.2020]
- Новые констукторы AbstractMetaSet, FilterMetaItemSet
- Упрощена структура Ramio::Meta::Description, разрешено копирование, указатель на описание типа теперь разделяемый

## 0.1.4d3 FilterMetaItemSet [22.01.2020]
- Новый фильтрующий набор FilterMetaItemSet, наследуемый от AbstractMetaSet
- Установка списка связей в AbstractMetaSet
- Вызов сигнала изменения элемента в фильрующем наборе
- Отключены проверки наличия элемента в списке при обработке изменения и удаления

## 0.1.4d2 Рефакторнирг && initSubComponents [21.01.2020]
- Добавлен метод Components::initSubComponents для объединения нескольких наборов в единый набор
- Незначительные изменения по стилистике кода

## 0.1.4d addItem -> insertItem [20.01.2020]
- Изменение сигнатур методов добавления элементов

## 0.1.4c4 Переделаны коды возврата [18.01.2020]
- Коды структуры возврата ResDesc изменили порядок
- Новый метод добавления списка элементов в набор

## 0.1.4c3 Функции для метавывода без параметра [15.01.2020]
- Используется правильный указатель на функцию из vtable, параметр объекта стуктуры больше не нужен
- Детектор полей убран в пространство имён Ramio
- Убрана излишняя виртуальность методов data() у элементов

## 0.1.4c2 Формат времени в логе [14.01.2020]
- Установка пользовательской функции генерации теста времени в логах

## 0.1.4c Переименование макроса экспорта [11.01.2020]
- Макрос DLL_EXPORT переименован в RAMIO_LIB_EXPORT 

## 0.1.4b7 Обновлено поведение Description::fieldIndexes [09.01.2020]
- Возможность вывода сообщения в лог при неуспешной попытке найти индекс поля

## 0.1.4b6 TableWidget::setColumns [08.01.2020]
- Новый меток для установки колонок в таблицах

## 0.1.4b5 DecorationRole [25.12.2019]
- Добавлена роль DecorationRole функций для отображения икнонок в таблицах

## 0.1.4b4 uuid [22.12.2019]
- Проверка поля uuid по наличию в мета-информации, использование в классах протокола, виджете редактирования
- Пример описание мета-структуры в примерах подправлен через использование предвариетльного описания 

## 0.1.4b3 FunctionRoles [21.12.2019]
- Перечисление FunctionRoles для индексациии функций в мета описании взамен строковому параметру
- Сигнатура функций изменена, возвращает QVariant, дополнительно принимает описание поля
- Строковый индекс "BackgroundColorRole" заменён на Meta::FunctionRoles::BackgroundColorRole

## 0.1.4b2 diff [19.12.2019]
- Property.dif переименован в Property.diff
- Новый метод fieldDiff у стурктуры мета информации
- Подправлен тест

## 0.1.4b Макросы для герерации классов изменены [18.12.2019]
- Новые макросы для генерации базового класса
- Макросы генерации мета списков сокращены

## 0.1.4a Макросы для расширенного мета списка [16.12.2019]
- Макросы GENERATE_CLASS_METABASESET и подобрые
- Размер поля типа сокращен до Short, подправлены функции описания типа
- Удалёна из конструктора обычного списка структура описания типов
- Подправлены примеры

## 0.1.4 Сжатие базовой структуры [15.12.2019]
- Из стуктуры ItemData удалены поля uuid, type, оставлен только id
- BaseMetaItemData переименован AbstractMetaItemData
- Новая структура MetaBaseItemData с полями uuid, type, state, flags
- Новый класс BaseItem для использования стуктур, наследуемых от MetaBaseItemData, предоставляет интерфейс удалённый из ItemData
- Новый шаблонный класс элментом MetaBaseItemSet для BaseItem
- Класс StructItem детектирует наличие поля uuid в шаблонном параметре и предоставляет интерфейс для работы с uuid (удалнный из ItemData)
- Подправлены остальные классы, связанные с этими изменениями
- В некоторых вспомогательных классах временно недоступен uuid у элементов (например в протоколе передачи по сети)
- Подправлены примеры, тесты
*работы по сжатию не завершены*

- Удален закоментированный код в PacketBuilder

## 0.1.3k2 DLL_EXPORT для новых классов [10.12.2019]
- DLL_EXPORT для классов ConnectionHandler, KeyValueRecord и некоторых функций из пространства Meta
- Удален закоментированный код в PacketBuilder

## 0.1.3k Сборка под GCC из поставки Ubuntu LTS [06.12.2019]
- Id и Uid в пакетах событий DataObjectCreated, DataObjectChanged
- В модели MetaItemsModel получения адреса функции через union DataFunctionPrt, взамен сложного каста.                                                                          
- Сборка метатипов на GCC 7.4 
- Коллекция наборов Components дополнилась сигналами изменения элементов в наборах
- Убране некоторые предупреждения компилятора

## 0.1.3j Упрощение класса логирования [27.11.2019]
- Макросы логов ничего больше не возвращают, в планах добавить JLOG
- TcpCoreServer возвращает статус успеха открытия порта на метод start()
- Удаление из набора элементов по константной ссылке

## 0.1.3i2 Абсракция клиента TCP [26.11.2019]
- Класс TcpServerHandler для предоставления базового TCP клиента
- Аргумент командной строки FULLLOG для логирования всех потоков

## 0.1.3i Начало создания абстракций передачи по сети [25.11.2019]
- Абстрактный класс для соединений ConnectionHandler 
- Класс TcpServerHandler для предоставления базового TCP сервера
- Метод мета информации fieldName переименован в fieldProtoName

## 0.1.3h Незначительные улучшения [19.11.2019]
- Методы сортировки в MetaItemSet
- Второй вариант функции selectMetaItemDataSet для запроса данных их базы данных
- Деструкторы для структур, чтобы уменьшить объектный код
- Фикс сборки под windows

## 0.1.3g Значение перечисления в конкретный тип, значение в строковое представление [16.11.2019]
- Конвертация значения Meta::Type в тип, через RMetaType::type
- Преобразования значения в строку через шаблонную функцию valueToString
- Сериализация времени с милисекундами
- Частичная реализация для типа Meta::Type::Char
- Расширен тест сериализации

## 0.1.3f Новые поддерживаемые типы, фиксы, рефакторинг [15.11.2019]
- Новые типы Meta::Type::String и Meta::Type::ByteArray
- Добавлен метод addItem в StructItemSet с перемещением объекта
- К набором добавлены методы createItem с перемещением структуры в создаваемый объект
- Новый упрощённый конструктор MetaItemSet
- Сериализация ItemData перенесена в отдельный файл
- Методы items всегда возвращают ссылку на список
- Фикс экспорта TcpServer
- Фикс сохранения денежного типа в XML
- Большое количество внутренних изменен

## 0.1.3e Рефакторинг [30.10.2019]
- Изменён порядок переменных uid и type
- Перечисление FieldType переименовано в FieldRole 
- Функции equals, less перенесены в пространство имёт Meta

## 0.1.3d Тест, сборка, рефакторинг [15.10.2019]
- Переименованы основные виджеты отображения, редактирования метаэлементов
- Добавлена сериализация всего сета в QJsonArray
- Проброшены методы begin/end в MetaItemSet для итерирования по списку
- Поиск через кэш по идентификаторам в MetaItemSet переписан
- Тест сериализации элемента
- Скрипты сборки дополнены
- Подправлены примеры использования

## 0.1.3c Переделка TCP, добавление SSL соединения [12.10.2019]
- Создание метаинформации: каст указателей через std::byte*, а не через char*
- Функция less() перенесена в MetaItemData
- Новые классы для SSL соединения (работа не завершена)
- Иерархия классов TCP соединений изменена
- Новый проект MetaItemTest для проверки свойств элементов
- Новые файлы Qt*Usage для использования прекомпиленных хедеров

## 0.1.3b Добавлены новые поддерживаемые типы из C++ [26.09.2019]
- Новые типы: RMetaShort RMetaUShort RMetaUInt RMetaULong RMetaFloat RMetaByte
- Для новых типов дописаны сериализация, взаимодействие с БД, отображение в интерфейсе
- Новый метод добавления элементов через список указателей
- Добавлена функция сравнения полей структур для всех типов
- Упрощена сортирующая модель
- Устранено одно ложное предупреждение о преобразовании данных при компиляции 
- Переименован DatabaseConfig
- Подправлены скриты сборки

## 0.1.3a Оптимизация вставки && Переработка денежного типа* [21.09.2019]
- При добавлении убраны принудительные проверки наличия элемента в списке
- Проверки проводятся через Q_ASSERT с ключенным макросом FULL_ASSERTS
- В денежном типе понижена точность дробной части с double до 2х цифр (работа не завершена)
- Добавлен частный макрос RMETA_OBJECT_BEGIN для RMETA_OBJECT_START(Ramio::MetaItemData)
- Расширена точность double при запрсак к БД
- Вывод в лог ошибки при запросе selectMetaItemDataSet в БД

## 0.1.3 Переименование основного макроса определения метасвойства [07.09.2019]
- Макрос RMETA_OBJECT_FIELD переименован в RMETA_OBJECT_PROPERTY
- Под макросом RMETA_OBJECT_FIELD определяется упрощенное описание из 3х параметров: имя, тип, описание
- Макрос RMETA_OBJECT_FIELD_C задаёт обозначение в протокольной части в стиле CamelCase
- Новые макросы GENERATE_CLASS_START и GENERATE_CLASS_METASET_START для начала описания классов
- QtCoreDeclaration для минимального описания необходимых типов
- Устранены некоторые опечатки
- Фикс создания схемы таблицы
- Подправлены примеры и ридми под новые макросы

## 0.1.2j MetaBool [06.08.2019]
- Добавлен поддерживаемый метатип Boolean
- Стандартный табличный виджет получил более простой конструктор
- Конструктор детализированного виджета элемента может принимать более конкретный параметр метаобъекта 
- Фикс: добавление в сет элемента по структуре происходит через фабрику объектов

## 0.1.2i Добавление элементов за раз [01.07.2019]
- Часть реализации MetaItemSet вынесена в отдельный файл
- Добавлены константные методы поиска по идентификаторам в списке мета элементов
- Фикс излишнего создания колонок таблиц для функций и временных переменных
- Метод addItems для добавления списка элементов за раз с одним сигналом полной перезагрузки
- Фильтрующий виджет для таблиц получил хоткей и индикатор активности фильтра
- В сохранение настроек добавлен класс QDateTimeEdit
- Макрос UI_CREATE_TOOLBAR требует указать к какому сетке его применять

## 0.1.2h Объявление и реализация метасвойств разделены [19.06.2019]
- Для макроса метаописания RMETA_OBJECT_START представлена альтернатива RMETA_OBJECT_DECL+RMETA_OBJECT_IMPL
- Макросы SAVE/LOAD SETTINGS обёрнуты в скобки

## 0.1.2g Правка макросов [10.06.2019]
- Макросы SAVE/LOAD_SETTINGS, задают имя объекта, если не задан
- Структура ResDesc перемещена в пространство имён Ramio
- Исправлена опечатка в макросах с LAUOUT на LAYOUT
- Скрипт сборки примеров выводит время начала, конца компиляции

## 0.1.2f Equals && renaming [31.05.2019]
- New functions equals() and equalsData() for MetaItemData
- Const meta description function registerMetaFields()
- Operator << move to stream QDebug for MetaItemData
- Functions renamed: saveMetaItemData() to insertMetaItemData(), selectMetaItemData() to selectMetaItemDataSet()
- Warnings removed at build scripts

## 0.1.2e NLOG && GuiDecl [24.05.2019]
- Fix double value deserialization from dom document
- New log type - notice
- QtWidgetsDeclaration header

## 0.1.2d Task function examples [22.05.2019]
- Example meta function usage
- Example meta sub functions usage
- Fix: meta values and functions not load from database
- New method - TableWidget::selectItem

## 0.1.2c Mini fixes [06.05.2019]
- Text color macros
- Rerurn error in query when database not open 

## 0.1.2b Quick search by identifier [25.04.2019]
- Optional quick search by id/uuid
- Disable DLOG and PLOG by default
- Init log settings from arguments
- New Hotkey actions: exit, fullscreen

## 0.1.2a Examples [25.04.2019]
- Example ItemSetClient is building
- Example ItemSetServer: make Users, print error if not starting
- New function config().filename()

## 0.1.2 Remastering [22.04.2019]
- Move some classes to project Smitto
- Change sub projects
- Changelog created
- Know erros: example ItemSetClient is not building

## 0.1.1i~~g~~ KeyValueRecord & Remove warnings ~~Log colors~~ [20.04.2019]
- Key-value record string
- Empty string changing
- Remove warning

## 0.1.1h~~i~~ Log colors [14.04.2019]
- Log colors at console
- Datetime at log
- New log type - warning
- Exit Codes and ExitHelper for linux
- Realization GetDataObject answer packet
- Table name for mysql/sqlite use schemename as prefix
- TableWidget currentItem() return selected item

## 0.1.1g~~f~~ GetDataObject packet [07.04.2019]
- SelectFirstMenuItem in MenuStackedWidget
- Realization GetDataObject answer packet

## 0.1.1f~~e~~ Fixes [26.03.2019]
- RAMIO_DIRECT build define
- Item destructor
- log messages

## 0.1.1e~~d~~ Test support MySQL [12.03.2019]
- Create Table for MySQL
- Lower db fieldnames
- Change description

## 0.1.1d~~e~~ Minimal changes [ 19.02.2019]
- UI Sets for QTextEdit
- Optional logging for TCP Server

## 0.1.1c~~d~~ Meta::FieldType::Function [ 19.02.2019]
- Experemental meta description for functions

## 0.1.1b Meta::Value [12.02.2019]
- Value of Meta::FieldType::Value used for local varable, not serialized and deserialized,
- UiSets for QTabWidget

## 0.1.1a ItemChanger [10.02.2019]
- change data and emit signal about changing item

## 0.1.1 Table scheme [07.02.2019]
- constraint fkey for different scheme
- fix saveType at ItemWidgetHelper

## 0.1.0i Table scheme name [06.02.2019]
- SchemeName for ItemSets, using in database
- l4StyleSheet for MenuStackedWidget

## 0.1.0h New type 'Date' and serialize to JSon [10.01.2019]
- Meta::Type::Date
- Const extern emptyString for direct using (not for dynamic linking)
- Ramio::uiSets().sync() if static object not destroyed
- AbstractMetaSet item's data serialize to QJsonObject
- Test: comparison item's field

## 0.1.0g New types 'Long' and 'Time' [05.01.2019]
- Meta::Type::Long
- Meta::Type::Time
- Some minor changes

## 0.1.0f Refactoring [21.10.2018]
- Include dir
- MetaItems sort filter model
- More functions fot meta items
- Build scripts
- Remanes

## 0.1.0e Build fix && Readme [01.09.2018]
- example using MetaItemSet

## 0.1.0d TypeDescription && ItemEditWidget [30.08.2018]
- TypeDescription for MetaItem->type()
- MetaItemSet creates with std::unique_ptr<Meta::TypeDescription>()
- CreateBaseWidget renamed to ItemEditWidget
- ItemEditWidget supports changing items
- ItemEditWidget supports TypeDescriptions values at ComboBox
- r_emptyString() emptyStringList() for empty reference
- examples update

## 0.1.0c Refactoring [28.08.2018]
- optional log at database, use application argument - PLOG_DATABASE
- more ranges for double and datetime at edit widget
- MetaDescription at single file
- replace Q_FOREACH(it, set) on for(it: set)
- TypeDescription for next purpose

## 0.1.0b New command at Protocol [01.07.2018]

## 0.1.0a Proto:DeleteItem [30.06.2018]
- Remove task at example
- ResDesc::setResDesc

## 0.1.0 - Merge branch 'blackbox' into preproduction [28.06.2018]
Move library from home pet project

## [26.06.2018]
Created repository
