
#include <QCoreApplication>
#include <QDebug>
#include <QObject>
#include <QQmlComponent>

#include "QQmlEngine"
#include "src/Components/DataComponents/FreeMemoryDataModel/FreeMemoryDataModel.h"
using namespace std;

int main(int argc, char **args) {
  //  QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
  //  QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
  //
  QCoreApplication application(argc, args);
  //  cout << QFile::exists(QStandardPaths::locate(
  //              QStandardPaths::StandardLocation::ConfigLocation,
  //              "AwesomeMonitor", QStandardPaths::LocateOption::LocateFile))
  //       << endl;

  //
  //  /* display result */
  //  printf("%s\n", inet_ntoa(((struct sockaddr_in
  //  *)&ifr.ifr_addr)->sin_addr));
  //  auto sp = new Plugin();
  //  sp->initializePlugin();
  //

  QQmlComponent c(new QQmlEngine,
                  "/home/kwan/0CC4-8589/AwesomeMonitor/defaultConfig/"
                  "DataModels/FreeMemoryDataModel/"
                  "FreeMemoryDataModel.qml");

  qDebug() << c.errorString();

  auto dataModel = qobject_cast<FreeMemoryDataModel *>(c.create());
  QObject::connect(dataModel, &FreeMemoryDataModel::currentValueChanged,
                   [](QVariant value) -> void { qDebug() << value; });

  return application.exec();
}
