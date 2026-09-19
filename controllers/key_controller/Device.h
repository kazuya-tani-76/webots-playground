/*!
 * \file Device.h
 * \brief デバイスモジュールヘッダファイル
 * \details 車両の各デバイスをまとめて管理する
 * \author T.K <kuzumaki@tfusion.co.jp>
 * \see Device.c
 */
#ifndef DEVICE_H_INCLUDED
#define DEVICE_H_INCLUDED

/*------------------------------------------------------------------------------
 * include
 *----------------------------------------------------------------------------*/
#include <webots/types.h>
#include <stdbool.h>

/*------------------------------------------------------------------------------
 * struct
 *----------------------------------------------------------------------------*/
/*!
 * \brief Webotsデバイス一覧
 */
typedef struct Device {
	/* 制御デバイス */
	WbDeviceTag	left_motor;				/*!< 左クローラ */
	WbDeviceTag	right_motor;			/*!< 右クローラ */
	WbDeviceTag	lift_motor;				/*!< リフト */
	WbDeviceTag	body_motor;				/*!< 車体 */
	WbDeviceTag	connector;				/*!< コネクタ */
	/* ライダ */
	WbDeviceTag	lidar_front;			/*!< 前方ライダ */
	WbDeviceTag	lidar_rear;				/*!< 後方ライダ */
	/* 位置センサ */
	WbDeviceTag	possensor_left_motor;	/*!< 左クローラ位置センサ */
	WbDeviceTag	possensor_right_motor;	/*!< 右クローラ位置センサ */
	WbDeviceTag	possensor_lift_motor;	/*!< リフト位置センサ */
	WbDeviceTag	possensor_body_motor;	/*!< 車体位置センサ */
	/* 距離センサ */
	WbDeviceTag	dissensor_lift;			/*!< リフト距離センサ */
	/* カメラ */
	WbDeviceTag	camera_lift;			/*!< リフトカメラ */
	WbDeviceTag	camera_front;			/*!< 車体前カメラ */
	WbDeviceTag	camera_bottom;			/*!< 車体底カメラ */
	WbDeviceTag	camera_rear;			/*!< 車体後カメラ */
} Device_t;

/*------------------------------------------------------------------------------
 * function
 *----------------------------------------------------------------------------*/
/*!
 * \brief Webotsデバイスを取得、初期化する
 * \param [out] device デバイス
 * \param [in] time_step Webotsの周期
 * \retval true 成功
 * \retval false 失敗
 */
bool DeviceInit(Device_t *device, int time_step);

#endif /* DEVICE_H_INCLUDED */
