/*!
 * \file Input.c
 * \brief 入力モジュールソースファイル
 * \details 
 * \author T.K <kuzumaki@tfusion.co.jp>
 * \see Input.h
 */
/*------------------------------------------------------------------------------
 * include
 *----------------------------------------------------------------------------*/
#include "Input.h"
#include <webots/keyboard.h>
#include <string.h>

/*------------------------------------------------------------------------------
 * define
 *----------------------------------------------------------------------------*/
/*!
 * \brief 最大キー
 */
#define MAX_KEY	(400)

/*------------------------------------------------------------------------------
 * private variable
 *----------------------------------------------------------------------------*/
/*!
 * \brief キー入力状態構造体
 */
typedef struct KeyState {
	bool	crnt;	/*!< 現在状態 */
	bool	prev;	/*!< 前回状態 */
} KeyState_t;

/*!
 * \brief キー入力状態
 */
static KeyState_t KeyState[MAX_KEY];

/*------------------------------------------------------------------------------
 * public function
 *----------------------------------------------------------------------------*/
/*!
 * \brief 入力管理を初期化する
 * \param [in] time_step シミュレータ周期
 */
void InputInit(int time_step)
{
	memset(&KeyState, 0, sizeof KeyState);
	wb_keyboard_enable(time_step);
}

/*!
 * \brief 入力状態を更新する
 */
void InputUpdate(void)
{
	int key;

	/* 前回状態を保存 */
	for (key = 0; key < MAX_KEY; ++key) {
		KeyState[key].prev = KeyState[key].crnt;
		KeyState[key].crnt = false;
	}
	/* キーボードイベントを取得 */
	while ((key = wb_keyboard_get_key()) != -1) {
		if (key >= 0 && key < MAX_KEY) {
			KeyState[key].crnt = true;
		}
	}
}

/*!
 * \brief 指定キーが押されているか判定する
 * \param [in] key Webotsキーコード
 * \retval true 押されている
 * \retval false 押されていない
 */
bool InputIsDown(int key)
{
	if (key < 0 || key >= MAX_KEY) {
		return false;
	}
	return KeyState[key].crnt;
}

/*!
 * \brief 指定キーが押された瞬間か判定する
 * \param [in] key Webotsキーコード
 * \retval true 押された瞬間
 * \retval false それ以外
 */
bool InputIsPressed(int key)
{
	if (key < 0 || key >= MAX_KEY) {
		return false;
	}
	return KeyState[key].crnt && !KeyState[key].prev;
}
