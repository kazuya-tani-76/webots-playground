/*!
 * \file CartMonitor.h
 * \brief 車両モニタモジュールヘッダファイル
 * \details 各センサ値をコンソールに出力する
 * \author T.K <kuzumaki@tfusion.co.jp>
 * \see CartMonitor.c
 */
#ifndef CARTMONITOR_H_INCLUDED
#define CARTMONITOR_H_INCLUDED

/*------------------------------------------------------------------------------
 * include
 *----------------------------------------------------------------------------*/
#include "Device.h"

/*------------------------------------------------------------------------------
 * function
 *----------------------------------------------------------------------------*/
/*!
 * \brief 車両モニタを初期化する
 * \param [in] device デバイス
 * \param [in] time_step シミュレータ周期
 */
void CartMonitorInit(const Device_t *device, int time_step);

/*!
 * \brief 車両センサ値を表示する
 */
void CartMonitorShow(void);

#endif /* CARTMONITOR_H_INCLUDED */
