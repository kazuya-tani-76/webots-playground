/*!
 * \file KeyConfig.h
 * \brief キー設定モジュールヘッダファイル
 * \details Inputが扱う物理キーと車両操作を分離する
 * \author T.K <kuzumaki@tfusion.co.jp>
 * \see KeyConfig.c
 */
#ifndef KEYCONFIG_H_INCLUDED
#define KEYCONFIG_H_INCLUDED

/*------------------------------------------------------------------------------
 * include
 *----------------------------------------------------------------------------*/
#include <stdbool.h>

/*------------------------------------------------------------------------------
 * type
 *----------------------------------------------------------------------------*/
/*!
 * \brief 車両操作
 */
typedef enum Action {
	ACTION_ACCEL = 0,		/*!< アクセル */
	ACTION_BRAKE,			/*!< ブレーキ */
	ACTION_TURN_LEFT,		/*!< 左旋回 */
	ACTION_TURN_RIGHT,		/*!< 右旋回 */
	ACTION_LIFT_UP,			/*!< リフト上昇 */
	ACTION_LIFT_DOWN,		/*!< リフト下降 */
	ACTION_BODY_LEFT,		/*!< 車体左回転 */
	ACTION_BODY_RIGHT,		/*!< 車体右回転 */
	ACTION_CONNECT,			/*!< コネクタ接続 */
	ACTION_DISCONNECT,		/*!< コネクタ切断 */
	ACTION_STOP,			/*!< 緊急停止 */
	ACTION_MAX				/*!< 最大数 */
} Action_t;

/*------------------------------------------------------------------------------
 * function
 *----------------------------------------------------------------------------*/
/*!
 * \brief 操作が実行中か判定する
 * \param [in] action 車両操作
 * \retval true 実行中
 * \retval false 実行中でない
 */
bool KeyConfigIsDown(Action_t action);

/*!
 * \brief 操作が開始された瞬間か判定する
 * \param [in] action 車両操作
 * \retval true 開始された瞬間
 * \retval false それ以外
 */
bool KeyConfigIsPressed(Action_t action);

#endif /* KEYCONFIG_H_INCLUDED */
