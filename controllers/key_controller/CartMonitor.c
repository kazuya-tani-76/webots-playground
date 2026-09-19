/*!
 * \file CartMonitor.c
 * \brief 車両モニタモジュールソースファイル
 * \author T.K <kuzumaki@tfusion.co.jp>
 * \see CartMonitor.h
 */
/*------------------------------------------------------------------------------
 * include
 *----------------------------------------------------------------------------*/
#include "CartMonitor.h"
#include "Config.h"
#include <webots/robot.h>
#include <webots/lidar.h>
#include <webots/connector.h>
#include <webots/position_sensor.h>
#include <webots/distance_sensor.h>
#include <stdio.h>

/*------------------------------------------------------------------------------
 * private prototype
 *----------------------------------------------------------------------------*/
static void ShowLidar(WbDeviceTag dev, const char *name);
static void ShowPositionSensor(WbDeviceTag dev, const char *name);
static void ShowDistanceSensor(WbDeviceTag dev, const char *name);
static void ShowCamera(WbDeviceTag dev, const char *name);
static void ShowConnector(WbDeviceTag dev, const char *name);

/*------------------------------------------------------------------------------
 * private variable
 *----------------------------------------------------------------------------*/
/*!
 * \brief デバイス
 */
static const Device_t *Device;

/*!
 * \brief シミュレータ周期
 */
static int TimeStep;

/*!
 * \brief モニタ表示経過時間(ms)
 */
static int MonitorTime;

/*------------------------------------------------------------------------------
 * public function
 *----------------------------------------------------------------------------*/
/*!
 * \brief 車両モニタを初期化する
 * \param [in] device デバイス
 * \param [in] time_step シミュレータ周期
 */
void CartMonitorInit(const Device_t *device, int time_step)
{
	if (device == NULL) {
		return;
	}
	/* デバイスを保持 */
	Device = device;
	/* シミュレータ周期を保持 */
	TimeStep = time_step;
	/* モニタ表示経過時間 */
	MonitorTime = 0;
}

/*!
 * \brief 車両センサ値を表示する
 */
void CartMonitorShow(void)
{
#if !CART_MONITOR_ENABLE
	return;
#endif
	if (Device == NULL) {
		return;
	}
	/* 表示周期を確認 */
	MonitorTime += TimeStep;
	if (MonitorTime < CART_MONITOR_INTERVAL) {
		return;
	}
	MonitorTime = 0;
	/* ライダ表示 */
#if CART_MONITOR_FRONT_LIDAR_ENABLE
	ShowLidar(Device->lidar_front, "FrontLidar");
#endif
#if CART_MONITOR_REAR_LIDAR_ENABLE
	ShowLidar(Device->lidar_rear, "RearLidar");
#endif
	/* 位置センサ表示 */
#if CART_MONITOR_LEFT_MOTOR_POSITION_ENABLE
	ShowPositionSensor(Device->possensor_left_motor, "LeftPosition");
#endif
#if CART_MONITOR_RIGHT_MOTOR_POSITION_ENABLE
	ShowPositionSensor(Device->possensor_right_motor, "RightPosition");
#endif
#if CART_MONITOR_LIFT_POSITION_ENABLE
	ShowPositionSensor(Device->possensor_lift_motor, "LiftPosition");
#endif
#if CART_MONITOR_BODY_POSITION_ENABLE
	ShowPositionSensor(Device->possensor_body_motor, "BodyPosition");
#endif
	/* 距離センサ表示 */
#if CART_MONITOR_LIFT_DISTANCE_ENABLE
	ShowDistanceSensor(Device->dissensor_lift, "LiftDistance");
#endif
	/* カメラ表示 */
#if CART_MONITOR_LIFT_CAMERA_ENABLE
	ShowCamera(Device->camera_lift, "LiftCamera");
#endif
#if CART_MONITOR_FRONT_CAMERA_ENABLE
	ShowCamera(Device->camera_front, "FrontCamera");
#endif
#if CART_MONITOR_BOTTOM_CAMERA_ENABLE
	ShowCamera(Device->camera_bottom, "BottomCamera");
#endif
#if CART_MONITOR_REAR_CAMERA_ENABLE
	ShowCamera(Device->camera_rear, "RearCamera");
#endif
#if CART_MONITOR_CONNECTOR_ENABLE
	/* コネクタ検出表示 */
	ShowConnector(Device->connector, "Connector");
#endif
}

/*------------------------------------------------------------------------------
 * private function
 *----------------------------------------------------------------------------*/
/*!
 * \brief ライダ値を表示する
 * \param [in] dev デバイス識別子
 * \param [in] name 表示名称
 */
static void ShowLidar(WbDeviceTag dev, const char *name)
{
	const WbLidarPoint *point;

	point = wb_lidar_get_point_cloud(dev);
	if (point != NULL) {
		printf("%s: (%f, %f, %f, %d)\n",
			name, point->x, point->y, point->z, point->layer_id);
	}
}

/*!
 * \brief 位置センサ値を表示する
 * \param [in] dev デバイス識別子
 * \param [in] name 表示名称
 */
static void ShowPositionSensor(WbDeviceTag dev, const char *name)
{
	double value;

	value = wb_position_sensor_get_value(dev);
	printf("%s: %f\n", name, value);
}

/*!
 * \brief 距離センサ値を表示する
 * \param [in] dev デバイス識別子
 * \param [in] name 表示名称
 */
static void ShowDistanceSensor(WbDeviceTag dev, const char *name)
{
	double value;

	value = wb_distance_sensor_get_value(dev);
	printf("%s: %f\n", name, value);
}

/*!
 * \brief カメラ値を表示する
 * \param [in] dev デバイス識別子
 * \param [in] name 表示名称
 */
static void ShowCamera(WbDeviceTag dev, const char *name)
{
	/* カメラはシミュレータにて視えるので一旦なし */
}

/*!
 * \brief コネクタ検出を表示する
 * \param [in] dev デバイス識別子
 * \param [in] name 表示名称
 */
static void ShowConnector(WbDeviceTag dev, const char *name)
{
	int presence;

	presence = wb_connector_get_presence(dev);
	switch (presence) {
	case 0:
		/* コネクタが存在しない */
		printf("%s: not detected\n", name);
		break;
	case 1:
		/* コネクタが存在する */
		printf("%s: detected!\n", name);
		break;
	default:
		/* 該当なし */
		break;
	}
}
