/*!
 * \file CartControl.c
 * \brief 車両制御モジュールソースファイル
 * \author T.K <kuzumaki@tfusion.co.jp>
 * \see CartControl.h
 */
/*------------------------------------------------------------------------------
 * include
 *----------------------------------------------------------------------------*/
#include "CartControl.h"
#include "Config.h"
#include <webots/motor.h>
#include <webots/connector.h>
#include <webots/position_sensor.h>
#include <stdio.h>

/*------------------------------------------------------------------------------
 * private prototype
 *----------------------------------------------------------------------------*/
static void SetDriveVelocity(double drive, double turn);
static void SetLiftVelocity(double lift);
static double GetLiftPosition(void);
static void SetBodyVelocity(double body);
static void Connect(void);
static void Disconnect(void);

/*------------------------------------------------------------------------------
 * private variable
 *----------------------------------------------------------------------------*/
/*!
 * \brief デバイス
 */
static const Device_t *Device;

/*!
 * \brief コネクタ接続状態
 * \details wb_connector_is_locked()の値ではなく、CartControlが接続切断を管理
 */
static bool ConnectorConnected;

/*------------------------------------------------------------------------------
 * public function
 *----------------------------------------------------------------------------*/
/*!
 * \brief 車両制御を初期化する
 * \param [in] device デバイス
 */
void CartControlInit(const Device_t *device)
{
	if (device == NULL) {
		return;
	}
	/* デバイスを保持 */
	Device = device;
	/* 初期状態は停止 */
	CartControlStop();
}

/*!
 * \brief 車両制御を更新する
 * \param [in] command 車両制御指令
 */
void CartControlUpdate(const CartCommand_t *command)
{
	if (command == NULL) {
		return;
	}
	/* 急停止 */
	if (command->stop) {
		CartControlStop();
		return;
	}
	/* 走行 */
	SetDriveVelocity(command->drive, command->turn);
	/* 車体旋回 */
	SetBodyVelocity(command->body);
	/* リフト */
	SetLiftVelocity(command->lift);
	/* コネクタ */
	if (command->connect) {
		Connect();
	}
	if (command->disconnect) {
		Disconnect();
	}
}

/*!
 * \brief 車両を停止する
 */
void CartControlStop(void)
{
	if (Device == NULL) {
		return;
	}
	wb_motor_set_velocity(Device->left_motor, 0.0);
	wb_motor_set_velocity(Device->right_motor, 0.0);
	wb_motor_set_velocity(Device->lift_motor, 0.0);
	wb_motor_set_velocity(Device->body_motor, 0.0);
}

/*------------------------------------------------------------------------------
 * private function
 *----------------------------------------------------------------------------*/
/*!
 * \brief 走行モータ速度を設定する
 * \param [in] drive 前後進入力
 * \param [in] turn 旋回入力
 */
static void SetDriveVelocity(double drive, double turn)
{
	double left, right;

	if (Device == NULL) {
		return;
	}
	/* 差動2輪方式 */
	left = (drive - turn) * TRACK_MAX_SPEED;
	right = (drive + turn) * TRACK_MAX_SPEED;
	/* モータ速度を制限 */
	if (left > TRACK_MAX_SPEED) {
		left = TRACK_MAX_SPEED;
	}
	if (left < -TRACK_MAX_SPEED) {
		left = -TRACK_MAX_SPEED;
	}
	if (right > TRACK_MAX_SPEED) {
		right = TRACK_MAX_SPEED;
	}
	if (right < -TRACK_MAX_SPEED) {
		right = -TRACK_MAX_SPEED;
	}
	wb_motor_set_velocity(Device->left_motor, left);
	wb_motor_set_velocity(Device->right_motor, right);
}

/*!
 * \brief リフト速度を設定する
 * \param [in] lift リフト入力
 */
static void SetLiftVelocity(double lift)
{
	double pos;

	if (Device == NULL) {
		return;
	}
	pos = GetLiftPosition();
	/* 上昇 */
	if (lift > 0.0) {
		if (pos >= LIFT_MAX_HEIGHT) {
			/* これ以上上昇させない */
			lift = 0.0;
		}
	}
	/* 下降 */
	if (lift < 0.0) {
		if (pos <= LIFT_MIN_HEIGHT) {
			/* これ以上下降させない */
			lift = 0.0;
		}
	}
	wb_motor_set_velocity(Device->lift_motor, lift * LIFT_SPEED);
}

/*!
 * \brief リフト位置を取得する
 * \return リフト位置
 */
static double GetLiftPosition(void)
{
	if (Device == NULL) {
		return INFINITY;
	}
	return wb_position_sensor_get_value(Device->possensor_lift_motor);
}

/*!
 * \brief 車体旋回速度を設定する
 * \param [in] body 車体旋回入力
 */
static void SetBodyVelocity(double body)
{
	if (Device == NULL) {
		return;
	}
	wb_motor_set_velocity(Device->body_motor, body * BODY_SPEED);
}

/*!
 * \brief コネクタを接続する
 */
static void Connect(void)
{
	if (Device == NULL) {
		return;
	}
	/* 既に接続済みなら何もしない */
	if (ConnectorConnected) {
		printf("conntected\n");
		return;
	}
	/* 接続対象が存在しなければ接続しない */
	if (wb_connector_get_presence(Device->connector) != 1) {
		printf("not found connector\n");
		return;
	}
	/* 接続要求 */
	wb_connector_lock(Device->connector);
	/* 接続状態に */
	ConnectorConnected = true;
	printf("connect OK\n");
}

/*!
 * \brief コネクタを切断する
 */
static void Disconnect(void)
{
	if (Device == NULL) {
		return;
	}
	/* 未接続なら何もしない */
	if (!ConnectorConnected) {
		printf("disconnected\n");
		return;
	}
	/* 切断 */
	wb_connector_unlock(Device->connector);
	/* 切断状態に */
	ConnectorConnected = false;
	printf("disconnect OK\n");
}
