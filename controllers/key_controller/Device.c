/*!
 * \file Device.c
 * \brief デバイスモジュールソースファイル
 * \author T.K <kuzumaki@tfusion.co.jp>
 * \see Device.h
 */
/*------------------------------------------------------------------------------
 * include
 *----------------------------------------------------------------------------*/
#include "Device.h"
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/lidar.h>
#include <webots/camera.h>
#include <webots/connector.h>
#include <webots/distance_sensor.h>
#include <webots/position_sensor.h>
#include <stdio.h>

/*------------------------------------------------------------------------------
 * private prototype
 *----------------------------------------------------------------------------*/
static bool InitControlDevice(Device_t *device, int time_step);
static bool InitMotor(WbDeviceTag *dev, const char *name);
static bool InitConnector(WbDeviceTag *dev, const char *name, int time_step);
static bool InitSensorDevice(Device_t *device, int time_step);
static bool InitLidar(WbDeviceTag *dev, const char *name, int time_step);
static bool InitPositionSensor(WbDeviceTag *dev, const char *name, int time_step);
static bool InitDistanceSensor(WbDeviceTag *dev, const char *name, int time_step);
static bool InitCamera(WbDeviceTag *dev, const char *name, int time_step);
static bool GetDevice(WbDeviceTag *dev, const char *name);

/*------------------------------------------------------------------------------
 * public function
 *----------------------------------------------------------------------------*/
/*!
 * \brief Webotsデバイスを取得、初期化する
 * \param [out] device デバイス
 * \param [in] time_step Webotsの周期
 * \retval true 成功
 * \retval false 失敗
 */
bool DeviceInit(Device_t *device, int time_step)
{
	if (device == NULL) {
		return false;
	}
	/* 制御デバイス初期化 */
	if (!InitControlDevice(device, time_step)) {
		return false;
	}
	/* センサデバイス初期化 */
	if (!InitSensorDevice(device, time_step)) {
		return false;
	}
	return true;
}

/*------------------------------------------------------------------------------
 * private function
 *----------------------------------------------------------------------------*/
/*!
 * \brief 制御デバイスを初期化する
 * \param [out] device デバイス
 * \param [in] time_step Webotsの周期
 * \retval true 成功
 * \retval false 失敗
 */
static bool InitControlDevice(Device_t *device, int time_step)
{
	if (device == NULL) {
		return false;
	}
	/* 左モータ */
	if (!InitMotor(&device->left_motor, "leftMotor")) {
		return false;
	}
	/* 右モータ */
	if (!InitMotor(&device->right_motor, "rightMotor")) {
		return false;
	}
	/* リフトモータ */
	if (!InitMotor(&device->lift_motor, "lift motor")) {
		return false;
	}
	/* 車体モータ */
	if (!InitMotor(&device->body_motor, "bodyMotor")) {
		return false;
	}
	/* コネクタ */
	if (!InitConnector(&device->connector, "connector", time_step)) {
		return false;
	}
	return true;
}

/*!
 * \brief モータを初期化する
 * \param [out] dev デバイス
 * \param [in] name デバイス名
 * \retval true 成功
 * \retval false 失敗
 */
static bool InitMotor(WbDeviceTag *dev, const char *name)
{
	if (dev == NULL || name == NULL) {
		return false;
	}
	/* デバイス取得 */
	if (!GetDevice(dev, name)) {
		return false;
	}
	/* 速度モード */
	wb_motor_set_position(*dev, INFINITY);
	wb_motor_set_velocity(*dev, 0.0);
	return true;
}

/*!
 * \brief コネクタを初期化する
 * \param [out] dev デバイス
 * \param [in] name デバイス名
 * \param [in] time_step Webotsの周期
 * \retval true 成功
 * \retval false 失敗
 */
static bool InitConnector(WbDeviceTag *dev, const char *name, int time_step)
{
	if (dev == NULL || name == NULL) {
		return false;
	}
	/* デバイス取得 */
	if (!GetDevice(dev, name)) {
		return false;
	}
	/* コネクタ検出有効化 */
	wb_connector_enable_presence(*dev, time_step);
	return true;
}

/*!
 * \brief センサデバイスを初期化する
 * \param [out] device デバイス
 * \param [in] time_step Webotsの周期
 * \retval true 成功
 * \retval false 失敗
 */
static bool InitSensorDevice(Device_t *device, int time_step)
{
	if (device == NULL) {
		return false;
	}
	/* 前方ライダ */
	if (!InitLidar(&device->lidar_front, "front lidar", time_step)) {
		return false;
	}
	/* 後方ライダ */
	if (!InitLidar(&device->lidar_rear, "rear lidar", time_step)) {
		return false;
	}
	/* 左クローラ位置センサ */
	if (!InitPositionSensor(&device->possensor_left_motor, "leftMotor position", time_step)) {
		return false;
	}
	/* 右クローラ位置センサ */
	if (!InitPositionSensor(&device->possensor_right_motor, "rightMotor position", time_step)) {
		return false;
	}
	/* リフト位置センサ */
	if (!InitPositionSensor(&device->possensor_lift_motor, "liftMotor position", time_step)) {
		return false;
	}
	/* 車体位置センサ */
	if (!InitPositionSensor(&device->possensor_body_motor, "body position", time_step)) {
		return false;
	}
	/* 距離センサ */
	if (!InitDistanceSensor(&device->dissensor_lift, "distance sensor", time_step)) {
		return false;
	}
	/* リフトカメラ */
	if (!InitCamera(&device->camera_lift, "lift camera", time_step)) {
		return false;
	}
	/* 車体前カメラ */
	if (!InitCamera(&device->camera_front, "front camera", time_step)) {
		return false;
	}
	/* 車体底カメラ */
	if (!InitCamera(&device->camera_bottom, "bottom camera", time_step)) {
		return false;
	}
	/* 車体後カメラ */
	if (!InitCamera(&device->camera_rear, "rear camera", time_step)) {
		return false;
	}
	return true;
}

/*!
 * \brief ライダを初期化する
 * \param [out] dev デバイス
 * \param [in] name デバイス名
 * \param [in] time_step Webotsの周期
 * \retval true 成功
 * \retval false 失敗
 */
static bool InitLidar(WbDeviceTag *dev, const char *name, int time_step)
{
	if (dev == NULL || name == NULL) {
		return false;
	}
	/* デバイス取得 */
	if (!GetDevice(dev, name)) {
		return false;
	}
	/* 測定有効化 */
	wb_lidar_enable(*dev, time_step);
	wb_lidar_enable_point_cloud(*dev);
	return true;
}

/*!
 * \brief 位置センサを初期化する
 * \param [out] dev デバイス
 * \param [in] name デバイス名
 * \param [in] time_step Webotsの周期
 * \retval true 成功
 * \retval false 失敗
 */
static bool InitPositionSensor(WbDeviceTag *dev, const char *name, int time_step)
{
	if (dev == NULL || name == NULL) {
		return false;
	}
	/* デバイス取得 */
	if (!GetDevice(dev, name)) {
		return false;
	}
	/* センサ有効化 */
	wb_position_sensor_enable(*dev, time_step);
	return true;
}

/*!
 * \brief 距離センサを初期化する
 * \param [out] dev デバイス
 * \param [in] name デバイス名
 * \param [in] time_step Webotsの周期
 * \retval true 成功
 * \retval false 失敗
 */
static bool InitDistanceSensor(WbDeviceTag *dev, const char *name, int time_step)
{
	if (dev == NULL || name == NULL) {
		return false;
	}
	/* デバイス取得 */
	if (!GetDevice(dev, name)) {
		return false;
	}
	/* センサ有効化 */
	wb_distance_sensor_enable(*dev, time_step);
	return true;
}

/*!
 * \brief カメラを初期化する
 * \param [out] dev デバイス
 * \param [in] name デバイス名
 * \param [in] time_step Webotsの周期
 * \retval true 成功
 * \retval false 失敗
 */
static bool InitCamera(WbDeviceTag *dev, const char *name, int time_step)
{
	if (dev == NULL || name == NULL) {
		return false;
	}
	/* デバイス取得 */
	if (!GetDevice(dev, name)) {
		return false;
	}
	/* 撮影有効化 */
	wb_camera_enable(*dev, time_step);
	return true;
}

/*!
 * \brief デバイスを取得する
 * \param [out] dev デバイス識別子
 * \param [in] name デバイス名
 * \retval true 成功
 * \retval false 失敗
 */
static bool GetDevice(WbDeviceTag *dev, const char *name)
{
	if (dev == NULL || name == NULL) {
		return false;
	}
	*dev = wb_robot_get_device(name);
	if (*dev != 0) {
		printf("%s ID = %d\n", name, *dev);
		return true;
	} else {
		printf("not found device '%s'\n", name);
		return false;
	}
}
