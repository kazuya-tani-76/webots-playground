/*!
 * \file CartCommand.c
 * \brief 車両操作指令ソースファイル
 * \author T.K <kuzumaki@tfusion.co.jp>
 * \see CartCommand.h
 */
/*------------------------------------------------------------------------------
 * include
 *----------------------------------------------------------------------------*/
#include "CartCommand.h"
#include "KeyConfig.h"
#include <string.h>

/*------------------------------------------------------------------------------
 * public fucntion
 *----------------------------------------------------------------------------*/
/*!
 * \brief 車両操作指令を更新する
 * \param [out] command 車両操作指令
 */
void CartCommandUpdate(CartCommand_t *command)
{
	memset(command, 0, sizeof *command);
	/* 緊急停止 */
	command->stop = KeyConfigIsDown(ACTION_STOP);
	if (command->stop) {
		/* 急停止中は他の操作を受け付けない */
		return;
	}
	/* 前進/後退 */
	if (KeyConfigIsDown(ACTION_ACCEL)) {
		command->drive += 1.0;
	}
	if (KeyConfigIsDown(ACTION_BRAKE)) {
		command->drive -= 1.0;
	}
	/* 左右旋回 */
	if (KeyConfigIsDown(ACTION_TURN_LEFT)) {
		command->turn += 1.0;
	}
	if (KeyConfigIsDown(ACTION_TURN_RIGHT)) {
		command->turn -= 1.0;
	}
	/* リフト上下 */
	if (KeyConfigIsDown(ACTION_LIFT_UP)) {
		command->lift += 1.0;
	}
	if (KeyConfigIsDown(ACTION_LIFT_DOWN)) {
		command->lift -= 1.0;
	}
	/* 車体回転 */
	if (KeyConfigIsDown(ACTION_BODY_LEFT)) {
		command->body += 1.0;
	}
	if (KeyConfigIsDown(ACTION_BODY_RIGHT)) {
		command->body -= 1.0;
	}
	/* コネクタ接続切断 */
	command->connect = KeyConfigIsPressed(ACTION_CONNECT);
	command->disconnect = KeyConfigIsPressed(ACTION_DISCONNECT);
}
