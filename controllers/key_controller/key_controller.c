/*!
 * \file key_controller.c
 * \brief キーボード制御メインプログラム
 * \author T.K <kuzumaki@tfusion.co.jp>
 */
/*------------------------------------------------------------------------------
 * include
 *----------------------------------------------------------------------------*/
#include "Config.h"
#include "Device.h"
#include "Input.h"
#include "KeyConfig.h"
#include "CartCommand.h"
#include "CartControl.h"
#include "CartMonitor.h"
#include <webots/robot.h>

/*------------------------------------------------------------------------------
 * public function
 *----------------------------------------------------------------------------*/
/*!
 * \brief エントリポイント
 * \param [in] argc コマンドライン引数の個数
 * \param [in] argv コマンドライン引数
 * \retval 0
 */
int main(int argc, char **argv)
{
	Device_t		device;
	CartCommand_t	command;

	/* Webotsシミュレータ初期化 */
	wb_robot_init();

	/* デバイス初期化 */
	if (!DeviceInit(&device, TIME_STEP)) {
		/* Webotsシミュレータ終了 */
		wb_robot_cleanup();
		return 1;
	}
	/* 入力初期化 */
	InputInit(TIME_STEP);
	/* 車両制御初期化 */
	CartControlInit(&device);
	/* 車両モニタ初期化 */
	CartMonitorInit(&device, TIME_STEP);

	/* メインループ */
	while (wb_robot_step(TIME_STEP) != -1) {
		/* 入力更新 */
		InputUpdate();
		/* 操作指令更新 */
		CartCommandUpdate(&command);
		/* 車両制御 */
		CartControlUpdate(&command);
		/* 車両モニタ表示 */
		CartMonitorShow();
	};

	/* 車両停止 */
	CartControlStop();
	/* Webotsシミュレータ終了 */
	wb_robot_cleanup();

	return 0;
}
