//
// Created by kwan on 1/28/19.
//

#include "JsonValueConverter.h"

#include <QFont>
#include <QQmlExpression>
#include <QtCore/QRectF>
#include <QtGui/QColor>
#include <QtQml/QJSValue>

#include "../../Components/ComponentUtils/utils.h"

const QVariant JsonValueConverter::convertBool(JsonValue value) {
  QVariant variant = value.get<bool>();
  return variant;
}
const QVariant JsonValueConverter::convertObject(JsonValue value) {
  if (value.contains("type") && defautlQmlTypesConverters.contains(
                                    value["type"].get<std::string>().c_str()))
    return (
        *this.*
        (defautlQmlTypesConverters[value["type"].get<std::string>().c_str()]))(
        value);
  QVariantMap variantMap;
  for (auto &item : value.items()) {
    variantMap.insert(QString(item.key().c_str()), convert(item.value()));
  }
  QVariant variant = variantMap;
  return QVariant(variant);
}
const QVariant JsonValueConverter::convertArray(JsonValue value) {
  QVariantList variantList;
  for (auto &item : value.items()) {
    variantList << convert(item.value());
  }
  QVariant variant = variantList;
  return variant;
}
const QVariant JsonValueConverter::convertString(JsonValue value) {
  QVariant variant = value.get<std::string>().c_str();
  return variant;
}
const QVariant JsonValueConverter::convertNumber(JsonValue value) {
  QVariant variant = value.get<double>();
  return variant;
}
const QVariant JsonValueConverter::convertNull(JsonValue value) {
  QVariant variant;
  return variant;
}
const QVariant JsonValueConverter::convert(JsonValue value) {
  if (functionMap.find(value.type()) == functionMap.end()) {
    qFatal(
        "RapidJson library has added new type. Json is probably dead :D or "
        "changed :(");
  }

  return (*this.*(functionMap[value.type()]))(value);
}
const QVariant JsonValueConverter::convertColor(nlohmann::json &object) {
  QColor value(object["value"].get<std::string>().c_str());
  return QVariant(value);
}
const QVariant JsonValueConverter::convertUrl(nlohmann::json &object) {
  QUrl value(object["value"].get<std::string>().c_str());
  return QVariant(value);
}

const QVariant JsonValueConverter::convertSize(nlohmann::json &object) {
  auto objectValue = object;
  QSizeF value(objectValue["width"].get<double>(),
               objectValue["height"].get<double>());
  return QVariant(value);
}
const QVariant JsonValueConverter::convertFont(nlohmann::json &object) {
  QFont value;
  for (auto &prop : object.items()) {
    if (fontSeters.contains(prop.key().c_str())) {
      (*this.*fontSeters[prop.key().c_str()])(value, prop.value());
    }
  }  // todo pridat dalsi setery
  return QVariant(value);
}
void JsonValueConverter::setItalic(QFont &font, nlohmann::json &object) {
  auto variant = convert(object);
  if (variant.type() == QVariant::Type::Bool) {
    font.setItalic(variant.toBool());
  }
}
void JsonValueConverter::setBold(QFont &font, nlohmann::json &object) {
  auto variant = convert(object);
  if (variant.type() == QVariant::Type::Bool) {
    font.setBold(variant.toBool());
  }
}
const QVariant JsonValueConverter::convertPoint(nlohmann::json &object) {
  auto objectValue = object;
  QPointF point(object["x"].get<double>(), objectValue["y"].get<double>());
  return QVariant(point);
}

const QVariant JsonValueConverter::convertRect(nlohmann::json &object) {
  auto objectValue = object;
  QRectF rect(object["x"].get<double>(), objectValue["y"].get<double>(),
              objectValue["width"].get<double>(),
              objectValue["height"].get<double>());
  return QVariant(rect);
}
const QVariant JsonValueConverter::convertEnum(nlohmann::json &object) {
  return QVariant(object["enumValue"].get<std::string>().c_str());
}
void JsonValueConverter::setComponent(QObject *object) { obj = object; }

const QVariant JsonValueConverter::convertFunction(nlohmann::json &object) {
  auto s = Utils::qjsEngine->evaluate(
      QString(object["value"].get<std::string>().c_str()));
  return QVariant::fromValue(s);
}

const QVariant JsonValueConverter::convertComponent(nlohmann::json &object) {
  auto componentDto = new ComponentDto();
  componentDto->url = QString(object["url"].get<std::string>().c_str());
  return QVariant::fromValue(componentDto);
}

const QVariant JsonValueConverter::convertItem(nlohmann::json &object) {
  return QVariant::fromValue(new ItemDto());
}

const QVariant JsonValueConverter::convertBind(nlohmann::json &object) {
  auto bind = new BindingDto;
  bind->binding = object["value"].get<std::string>().c_str();
  return QVariant::fromValue(bind);
}