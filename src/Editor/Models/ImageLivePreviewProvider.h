//
// Created by kwan on 24.11.20.
//

#ifndef AWESOMEMONITOR_IMAGELIVEPREVIEWPROVIDER_H
#define AWESOMEMONITOR_IMAGELIVEPREVIEWPROVIDER_H

#include <QQuickWindow>
#include <QtCore/QThreadPool>
#include <QtQuick/QQuickAsyncImageProvider>

class ImageProvider : public QQuickImageProvider {
  QVector<QQuickWindow *> m_windows;

 public slots:
  void pluginInitializing() { initializing = true; };
  void pluginInitialize(QVector<QQuickWindow *> windows) {
    m_windows = windows;
    initializing = false;
  };

 public:
  ImageProvider() : QQuickImageProvider(QQuickImageProvider::Image) {}
  QImage requestImage(const QString &id, QSize *size,
                      const QSize &requestedSize) override {
    auto number = id.toInt();
    if (!initializing && number >= 0 && m_windows.count() > number &&
        m_windows[number]) {
      qDebug() << "window";
      auto window = m_windows[number];
      window->setVisibility(QWindow::Hidden);
      auto image = window->grabWindow();
      return image;
    }
    qDebug() << "sdasdsa";
    return QImage();
  }

 private:
  bool initializing = true;
};

#endif  // AWESOMEMONITOR_IMAGELIVEPREVIEWPROVIDER_H
