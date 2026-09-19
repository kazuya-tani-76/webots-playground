/*!
 * \file CartCommand.h
 * \brief 車両操作指令ヘッダファイル
 * \details KeyConfigが作った操作を車両制御に渡すための操作指令を定義する
 * \author T.K <kuzumaki@tfusion.co.jp>
 * \see CartCommand.c
 */
#ifndef CARTCOMMAND_H_INCLUDED
#define CARTCOMMAND_H_INCLUDED

/*------------------------------------------------------------------------------
 * include
 *----------------------------------------------------------------------------*/
#include <stdbool.h>

/*------------------------------------------------------------------------------
 * type
 *----------------------------------------------------------------------------*/
/*!
 * \brief 車両操作指令
 */
typedef struct CartCommand {
	/*!
	 * \brief 走行(前進:+1.0/後退:-1.0/停止:0.0)
	 */
	double drive;

	/*!
	 * \brief 旋回(左旋回:+1.0/直進:0.0/右旋回:-1.0)
	 */
	double turn;

	/*!
	 * \brief リフト(上昇:+1.0/停止:0.0/下降:-1.0)
	 */
	double lift;

	/*!
	 * \brief 車体旋回(左回転:+1.0/停止:0.0/右回転:-1.0)
	 */
	double body;

	/*!
	 * \brief コネクタ接続
	 */
	bool connect;

	/*!
	 * \brief コネクタ切断
	 */
	bool disconnect;

	/*!
	 * \brief 緊急停止
	 */
	bool stop;
} CartCommand_t;

/*!
 * \brief 車両操作指令を更新する
 * \param [out] command 車両操作指令
 */
void CartCommandUpdate(CartCommand_t *command);

#endif /* CARTCOMMAND_H_INCLUDED */
