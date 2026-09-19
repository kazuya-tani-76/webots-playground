/*!
 * \file Config.h
 * \brief 設定ヘッダファイル
 * \details 調整値をまとめておく
 * \author T.K <kuzumaki@tfusion.co.jp>
 */
#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

/*------------------------------------------------------------------------------
 * include
 *----------------------------------------------------------------------------*/
#include <webots/keyboard.h>

/*------------------------------------------------------------------------------
 * キー設定
 *----------------------------------------------------------------------------*/
#define KEY_ACCEL		('W')				/*!< 前進 */
#define KEY_BRAKE		('S')				/*!< 後退/ブレーキ */
#define KEY_TURN_LEFT	('A')				/*!< 左旋回 */
#define KEY_TURN_RIGHT	('D')				/*!< 右旋回 */
#define KEY_LIFT_UP		WB_KEYBOARD_UP		/*!< リフト上昇 */
#define KEY_LIFT_DOWN	WB_KEYBOARD_DOWN	/*!< リフト下降 */
#define KEY_BODY_LEFT	WB_KEYBOARD_LEFT	/*!< 車体左回転 */
#define KEY_BODY_RIGHT	WB_KEYBOARD_RIGHT	/*!< 車体右回転 */
#define KEY_CONNECT		('C')				/*!< コネクタ接続 */
#define KEY_DISCONNECT	('X')				/*!< コネクタ切断 */
#define KEY_STOP		(' ')				/*!< 急停止 */

/*------------------------------------------------------------------------------
 * シミュレーション
 *----------------------------------------------------------------------------*/
#define TIME_STEP	(32)	/*!< シミュレーション周期(ms) */

/*------------------------------------------------------------------------------
 * クローラ
 *----------------------------------------------------------------------------*/
#define TRACK_MAX_SPEED		(3.0)	/*!< クローラ最大速度 */
#define TRACK_ACCELERATION	(0.15)	/*!< クローラ加速度(予約) */

/*------------------------------------------------------------------------------
 * リフト
 *----------------------------------------------------------------------------*/
#define LIFT_SPEED			(0.15)	/*!< リフト速度 */
#define LIFT_MAX_HEIGHT		(+0.50)	/*!< リフト最大高さ */
#define LIFT_MIN_HEIGHT		(-0.25)	/*!< リフト最小高さ */

/*------------------------------------------------------------------------------
 * 車体
 *----------------------------------------------------------------------------*/
#define BODY_SPEED			(1.0)	/*!< 車体旋回速度 */

/*------------------------------------------------------------------------------
 * 車両モニタ
 *----------------------------------------------------------------------------*/
#define CART_MONITOR_ENABLE		(1)		/*!< モニタ有効/無効 */
#define CART_MONITOR_INTERVAL	(500)	/*!< モニタ表示周期(ms) */
/* ライダ */
#define CART_MONITOR_FRONT_LIDAR_ENABLE	(0)	/*!< 前方ライダ */
#define CART_MONITOR_REAR_LIDAR_ENABLE	(0)	/*!< 後方ライダ */
/* 位置センサ */
#define CART_MONITOR_LEFT_MOTOR_POSITION_ENABLE		(0)	/*!< 左クローラ位置センサ */
#define CART_MONITOR_RIGHT_MOTOR_POSITION_ENABLE	(0)	/*!< 右クローラ位置センサ */
#define CART_MONITOR_LIFT_POSITION_ENABLE			(0)	/*!< リフト位置センサ */
#define CART_MONITOR_BODY_POSITION_ENABLE			(0)	/*!< 車体位置センサ */
/* 距離センサ */
#define CART_MONITOR_LIFT_DISTANCE_ENABLE	(0)	/*!< リフト距離センサ */
/* カメラ */
#define CART_MONITOR_LIFT_CAMERA_ENABLE		(0)	/*!< リフトカメラ */
#define CART_MONITOR_FRONT_CAMERA_ENABLE	(0)	/*!< 車体前カメラ */
#define CART_MONITOR_BOTTOM_CAMERA_ENABLE	(0)	/*!< 車体底カメラ */
#define CART_MONITOR_REAR_CAMERA_ENABLE		(0)	/*!< 車体後カメラ */
/* コネクタ */
#define CART_MONITOR_CONNECTOR_ENABLE	(1)	/*!< コネクタ */

#endif /* CONFIG_H_INCLUDED */
