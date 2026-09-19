/*!
 * \file KeyConfig.c
 * \brief キー設定モジュールソースファイル
 * \author T.K <kuzumaki@tfusion.co.jp>
 * \see KeyConfig.h
 */
/*------------------------------------------------------------------------------
 * include
 *----------------------------------------------------------------------------*/
#include "KeyConfig.h"
#include "Config.h"
#include "Input.h"

/*------------------------------------------------------------------------------
 * private variable
 *----------------------------------------------------------------------------*/
/*!
 * \brief 操作とキーの対応表
 */
static int KeyConfig[ACTION_MAX] = {
	/* 前進 */
	[ACTION_ACCEL]		= KEY_ACCEL,
	/* 後退/ブレーキ */
	[ACTION_BRAKE]		= KEY_BRAKE,
	/* 左旋回 */
	[ACTION_TURN_LEFT]	= KEY_TURN_LEFT,
	/* 右旋回 */
	[ACTION_TURN_RIGHT]	= KEY_TURN_RIGHT,
	/* リフト上昇 */
	[ACTION_LIFT_UP]	= KEY_LIFT_UP,
	/* リフト下降 */
	[ACTION_LIFT_DOWN]	= KEY_LIFT_DOWN,
	/* 車体左回転 */
	[ACTION_BODY_LEFT]	= KEY_BODY_LEFT,
	/* 車体右回転 */
	[ACTION_BODY_RIGHT]	= KEY_BODY_RIGHT,
	/* コネクタ接続 */
	[ACTION_CONNECT]	= KEY_CONNECT,
	/* コネクタ切断 */
	[ACTION_DISCONNECT]	= KEY_DISCONNECT,
	/* 急停止 */
	[ACTION_STOP]		= KEY_STOP,
};

/*------------------------------------------------------------------------------
 * public function
 *----------------------------------------------------------------------------*/
/*!
 * \brief 操作が実行中か判定する
 * \param [in] action 車両操作
 * \retval true 実行中
 * \retval false 実行中でない
 */
bool KeyConfigIsDown(Action_t action)
{
	if (action < 0 || action >= ACTION_MAX) {
		return false;
	}
	return InputIsDown(KeyConfig[action]);
}

/*!
 * \brief 操作が開始された瞬間か判定する
 * \param [in] action 車両操作
 * \retval true 開始された瞬間
 * \retval false それ以外
 */
bool KeyConfigIsPressed(Action_t action)
{
	if (action < 0 || action >= ACTION_MAX) {
		return false;
	}
	return InputIsPressed(KeyConfig[action]);
}
