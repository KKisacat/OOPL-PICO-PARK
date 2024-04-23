/*
 * mygame.h: ���ɮ��x�C��������class��interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/

#include "Character.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		void load_background();
		void draw_text();
		CMovingBitmap background;
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int phase = 1;
		int sub_phase = 1;
		CMovingBitmap catalog; //�ؿ�
		CMovingBitmap background;
		Character character1 = Character({ "resources/player1Rightstand.bmp",
			"resources/player1RightRun1.bmp",
			"resources/player1RightRun2.bmp",
			"resources/player1RightRun3.bmp",
			"resources/player1RightRun4.bmp" }, "Blue", 1020, 810);
		Character character2 = Character({ "resources/player2Rightstand.bmp",
			"resources/player2RightRun1.bmp",
			"resources/player2RightRun2.bmp",
			"resources/player2RightRun3.bmp",
			"resources/player2RightRun4.bmp" }, "Pink", 900, 810);
		CMovingBitmap block[1000];
		CMovingBitmap button;
		CMovingBitmap bridge;
		CMovingBitmap platform;
		CMovingBitmap pFlag;
		CMovingBitmap key;
		CMovingBitmap door;
		CMovingBitmap crown[4];
		CMovingBitmap clear;

		void show_image_by_phase();
		void show_text_by_phase();
		bool validate_phase_1();
		bool validate_phase_2();
		bool validate_phase_3();
		bool validate_phase_4();
		bool validate_phase_5();
		bool validate_phase_6();

		//���D
		int _P1UpTime = 0; 
		bool _isP1UpRun = 0;
		bool _P1JumpOnce = 0;
		int _P2UpTime = 0;
		bool _isP2UpRun = 0;
		bool _P2JumpOnce = 0;

		//���b
		int _mapMove = 0;

		//�樫
		bool _isRightRun = 0;
		bool _isLeftRun = 0;
		bool _P2isRightRun = 0;
		bool _P2isLeftRun = 0;


		//���| 
		bool buttonOverlap;
		bool keyP1Overlap;
		bool keyP2Overlap;
		bool bridgeP1Overlap;
		bool bridgeP2Overlap;
		bool platformP1Overlap;
		bool platformP2Overlap;
		bool P1onP2isOverlap;
		bool P2onP1isOverlap;
		bool doorP1isOverlap;
		bool doorP2isOverlap;
		
		//�_�͸��H
		int staybyPlayer1 = 0;
		int staybyPlayer2 = 0;
		bool keyIgnore = false;

		//�i�j��
		bool player1Ignore = false;
		bool player2Ignore = false;
		
		//�I��
		void CheckMovable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy); //�B�z���a�I��
		bool IsJumpable(CMovingBitmap & player, vector<CMovingBitmap> & targets, int dx, int dy);

	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
		void OnKeyDown(UINT, UINT, UINT);
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap background;
		void load_background();
	};

}