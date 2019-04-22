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
- ContentBaseWidget currentItem() return selected item

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

## 0.1.0d TypeDescription && ItemEditBaseWidget [30.08.2018]
- TypeDescription for MetaItem->type()
- MetaItemSet creates with std::unique_ptr<Meta::TypeDescription>()
- CreateBaseWidget renamed to ItemEditBaseWidget
- ItemEditBaseWidget supports changing items
- ItemEditBaseWidget supports TypeDescriptions values at ComboBox
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
