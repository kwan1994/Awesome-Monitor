

#include <Components/DataComponents/UploadSpeedDataModel/UploadSpeedDataModel.h>
#include <Editor/Models/PluginTreeModel/PluginTreeModel.h>
#include <Plugin.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h> /* for strncpy */
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <QAbstractItemModelTester>
#include <QApplication>
#include <QLibraryInfo>
#include <QtCore/QFile>
#include <QtQml/QQmlApplicationEngine>
#include <string>

using namespace std;

int main(int argc, char **args) {
  //  QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
  //  QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
  //
  // QApplication application(argc, args);
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
  // return application.exec();

  auto s = new PluginTreeModel();

  auto test = new QAbstractItemModelTester(
      s, QAbstractItemModelTester::FailureReportingMode::Warning);
  return 0;
}
