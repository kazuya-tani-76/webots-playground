/*!
 * \file CartControl.h
 * \brief 車両制御モジュールヘッダファイル
 * \author T.K <kuzumaki@tfusion.co.jp>
 * \see CartControl.c
 */
#ifndef CARTCONTROL_H_INCLUDED
#define CARTCONTROL_H_INCLUDED

/*------------------------------------------------------------------------------
 * include
 *----------------------------------------------------------------------------*/
#include "Device.h"
#include "CartCommand.h"

/*------------------------------------------------------------------------------
 * function
 *----------------------------------------------------------------------------*/
/*!
 * \brief 車両制御を初期化する
 * \param [in] device デバイス
 */
void CartControlInit(const Device_t *device);

/*!
 * \brief 車両制御を更新する
 * \param [in] command 車両制御指令
 */
void CartControlUpdate(const CartCommand_t *command);

/*!
 * \brief 車両を停止する
 */
void CartControlStop(void);

#endif /* CARTCONTROL_H_INCLUDED */
