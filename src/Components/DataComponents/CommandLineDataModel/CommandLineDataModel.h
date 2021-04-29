//
// Created by kwan on 15.08.19.
//

#ifndef COMPONENTS_COMMANDLINEDATAMODEL_H
#define COMPONENTS_COMMANDLINEDATAMODEL_H

#include "../DataModelBase.h"
#include <QtCore/QProcess>
class CommandLineDataModel: public DataModelBase {
  Q_OBJECT
  Q_PROPERTY(QString command READ command WRITE setCommand
                 NOTIFY commandChanged FINAL);
  QString _command = "";
  QProcess * process = new QProcess;
  void computeValue();
public:
  CommandLineDataModel(QObject * parent = nullptr);
  QString command();
  void setCommand(QString);
  signals:
    void commandChanged();


};



#endif //COMPONENTS_COMMANDLINEDATAMODEL_H
