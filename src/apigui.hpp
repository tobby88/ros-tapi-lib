#ifndef APIGUI_HPP
#define APIGUI_HPP

#include "api.hpp"
#include <QMainWindow>
#include <QTimer>
#include "apideviceswrapper.hpp"

namespace Ui
{
class ApiGui;
}

class ApiGui : public QMainWindow
{
  Q_OBJECT

public:
  explicit ApiGui(Api* api, QWidget* parent = 0);
  ~ApiGui();

private:
  Ui::ApiGui* ui;
  Api* api;
  unsigned long int temp;
  QTimer* timer;
  ApiDevicesWrapper* myModel;

private slots:
  void checkApiForUpdate();
};

#endif // APIGUI_HPP
