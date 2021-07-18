//
// Created by kwan on 1/28/19.
//

#ifndef AWESOMEMONITOR_JSONVALUECONVERTER_H
#define AWESOMEMONITOR_JSONVALUECONVERTER_H

#include <QtCore/QVariant>
#include <QtQml/QQmlEngine>
#include <nlohmann/json.hpp>
#include <unordered_map>

typedef nlohmann::json& JsonValue;

class JsonValueConverter {
  typedef const QVariant (JsonValueConverter::*ConverterFunction)(JsonValue);
  typedef void (JsonValueConverter::*FontSetter)(QFont&, JsonValue);

  QObject* obj;

  std::unordered_map<nlohmann::json::value_t, ConverterFunction> functionMap = {
      {nlohmann::json::value_t::boolean, &JsonValueConverter::convertBool},
      {nlohmann::json::value_t::object, &JsonValueConverter::convertObject},
      {nlohmann::json::value_t::array, &JsonValueConverter::convertArray},
      {nlohmann::json::value_t::number_integer,
       &JsonValueConverter::convertNumber},
      {nlohmann::json::value_t::number_unsigned,
       &JsonValueConverter::convertNumber},
      {nlohmann::json::value_t::number_float,
       &JsonValueConverter::convertNumber},
      {nlohmann::json::value_t::string, &JsonValueConverter::convertString},
      {nlohmann::json::value_t::null, &JsonValueConverter::convertNull}};

  QMap<QString, FontSetter> fontSeters =
      QMap<QString, FontSetter>({{"bold", &JsonValueConverter::setBold},
                                 {"italic", &JsonValueConverter::setItalic}});

  QMap<QString, ConverterFunction> defautlQmlTypesConverters =
      QMap<QString, ConverterFunction>(
          {{"bind", &JsonValueConverter::convertBind},
           {"function", &JsonValueConverter::convertFunction},
           {"color", &JsonValueConverter::convertColor},
           {"url", &JsonValueConverter::convertUrl},
           {"size", &JsonValueConverter::convertSize},
           {"font", &JsonValueConverter::convertFont},
           {"rect", &JsonValueConverter::convertRect},
           {"point", &JsonValueConverter::convertPoint},
           {"enum", &JsonValueConverter::convertEnum},
           {"component", &JsonValueConverter::convertComponent},
           {"item", &JsonValueConverter::convertItem}});

  void setItalic(QFont&, JsonValue);
  void setBold(QFont&, JsonValue);

  const QVariant convertEnum(JsonValue);
  const QVariant convertPoint(JsonValue);
  const QVariant convertRect(JsonValue);
  const QVariant convertFont(JsonValue);
  const QVariant convertSize(JsonValue);
  const QVariant convertUrl(JsonValue);
  const QVariant convertColor(JsonValue);
  const QVariant convertBool(JsonValue);
  const QVariant convertObject(JsonValue);
  const QVariant convertArray(JsonValue);
  const QVariant convertNumber(JsonValue);
  const QVariant convertString(JsonValue);
  const QVariant convertNull(JsonValue);
  const QVariant convertBind(JsonValue);
  const QVariant convertFunction(JsonValue);
  const QVariant convertComponent(JsonValue);

 public:
  QQmlEngine* engines;
  const QVariant convert(JsonValue);
  void setComponent(QObject*);
  const QVariant convertItem(nlohmann::json& object);
};

class BindingDto {
 public:
  QString binding;
};

class ItemDto {};

class ComponentDto {
 public:
  QString url;
};

Q_DECLARE_METATYPE(BindingDto*);

Q_DECLARE_METATYPE(ItemDto*);

Q_DECLARE_METATYPE(ComponentDto*);

#endif  // AWESOMEMONITOR_JSONVALUECONVERTER_H
