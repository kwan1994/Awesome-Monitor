//
// Created by kwan on 15.08.19.
//

#include "CommandLineDataModel.h"

#include "qdebug.h"

CommandLineDataModel::CommandLineDataModel(QObject *parent)
    : DataModelBase(parent, "defaultReturnTransformer") {
  process = new QProcess(this);
  QObject::connect(_timer, &QTimer::timeout,
                   [this]() -> void { computeValue(); });
  QObject::connect(
      process,
      (void (QProcess::*)(int, QProcess::ExitStatus)) & QProcess::finished,
      [this](int exitCode, QProcess::ExitStatus status) -> void {
        setCurrentValue(process->readAllStandardOutput(), true);
      });
  restartTimer();
}

QString CommandLineDataModel::command() { return _command; }

void CommandLineDataModel::setCommand(QString command) {
  _command = command;
  emit commandChanged();
}

void CommandLineDataModel::computeValue() {
  if (process->state() == QProcess::NotRunning) {
    process->start("bash", QStringList() << "-c" << _command);
  }
}