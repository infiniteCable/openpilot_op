#pragma once

#include <QPainter>
#include "selfdrive/ui/ui.h"
#include "common/params.h"
#include "cereal/messaging/messaging.h"

class HudRenderer : public QObject {
  Q_OBJECT

public:
  HudRenderer();
  void updateState(const UIState &s);
  void draw(QPainter &p, const QRect &surface_rect);

private:
  void triggerParentUpdate();
  void drawSetSpeed(QPainter &p, const QRect &surface_rect);
  void drawCurrentSpeed(QPainter &p, const QRect &surface_rect);
  void drawText(QPainter &p, int x, int y, const QString &text, int alpha = 255);
  void drawIcon(QPainter &p, const QPoint &center, const QPixmap &img, const QBrush &bg, float opacity);
  void drawBatteryHeaterIcon(QPainter &p, const QRect &surface_rect);
  void drawBatteryDetailsPanel(QPainter &p, const QRect &surface_rect);

  float speed = 0;
  float set_speed = 0;
  bool is_cruise_set = false;
  bool is_metric = false;
  bool v_ego_cluster_seen = false;
  int status = STATUS_DISENGAGED;
  bool battery_heater_enabled = false;
  QPixmap img_battery_heater_enabled;
  QPixmap img_battery_heater_disabled;
  const int btn_size = 192;
  const int img_size = (btn_size / 4) * 3;

  struct BatteryDetails {
    bool heaterActive = false;
    float capacity = 0.0f;       // Wh
    float charge = 0.0f;         // Wh
    float soc = 0.0f;            // %
    float temperature = 0.0f;    // °C
    float cellVoltage = 0.0f;    // V
    float voltage = 0.0f;        // V
    float current = 0.0f;        // A
    float currentMax = 0.0f;     // A
    float power = 0.0f;          // W
    float powerMax = 0.0f;       // W
  };

  BatteryDetails battery_details;

};
