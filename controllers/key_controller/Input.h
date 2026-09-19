/*!
 * \file Input.h
 * \brief 入力モジュールヘッダファイル
 * \details キーボード入力を管理する
 * \author T.K <kuzumaki@tfusion.co.jp>
 * \see Input.c
 */
#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

/*------------------------------------------------------------------------------
 * include
 *----------------------------------------------------------------------------*/
#include <stdbool.h>

/*------------------------------------------------------------------------------
 * function
 *----------------------------------------------------------------------------*/
/*!
 * \brief 入力管理を初期化する
 * \param [in] time_step シミュレータ周期
 */
void InputInit(int time_step);

/*!
 * \brief 入力状態を更新する
 */
void InputUpdate(void);

/*!
 * \brief 指定キーが押されているか判定する
 * \param [in] key Webotsキーコード
 * \retval true 押されている
 * \retval false 押されていない
 */
bool InputIsDown(int key);

/*!
 * \brief 指定キーが押された瞬間か判定する
 * \param [in] key Webotsキーコード
 * \retval true 押された瞬間
 * \retval false それ以外
 */
bool InputIsPressed(int key);

#endif /* INPUT_H_INCLUDED */
