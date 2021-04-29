

#include <Plugin.h>

#include <QApplication>
#include <QLibraryInfo>
#include <QtCore/QFile>
#include <string>

using namespace std;

int main(int argc, char **args) {
  QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
  QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);

  QApplication application(argc, args);
  cout << QFile::exists(QStandardPaths::locate(
              QStandardPaths::StandardLocation::ConfigLocation,
              "AwesomeMonitor", QStandardPaths::LocateOption::LocateFile))
       << endl;

  auto sp = new Plugin();
  //    QQmlApplicationEngine engine(
  //        "/home/kwan/0CC4-8589/AwesomeMonitor/plasmoid/contents/ui/Editor.qml");
  sp->initializePlugin();
  return application.exec();
}
