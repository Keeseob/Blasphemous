#include "keyInput.h"

namespace BP
{
	int ASCII[(UINT)eKeyCode::end] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',

		VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_SPACE,
	};

	std::vector<keyInput::key> keyInput::mKey;

	void keyInput::initialize()
	{
		for (UINT i = 0; i < (UINT)eKeyCode::end; i++)
		{
			key keyInfo;
			keyInfo.keyCode = (eKeyCode)i;
			keyInfo.keyState = eKeyState::none;
			keyInfo.pressCheck = false;

			mKey.push_back(keyInfo);
		}
	}
	void keyInput::update()
	{
		for (UINT i = 0; i < (UINT)eKeyCode::end; i++)
		{
			if (GetAsyncKeyState(ASCII[i]) & 0x8000) //현재 키보드를 누르고 있는 경우
				//GetAsyncKeyState: 현재 키 상태를 알리는 함수
			{
				if (mKey[i].pressCheck) //이전 프레임에 키가 눌려있을 경우
				{
					mKey[i].keyState = eKeyState::pressed; //press인식
				}
				else //이전 프레임에 키가 눌려있지 않을 경우
				{
					mKey[i].keyState = eKeyState::down; //down인식
				}
				mKey[i].pressCheck = true;
			}
			else //현재 키보드를 누르지 않는 경우
			{
				if (mKey[i].pressCheck) //이전 프레임에 키가 눌려있는 경우
				{
					mKey[i].keyState = eKeyState::up; //up인식
				}
				else //이전 프레임에 키가 눌려있지 않을 경우
				{
					mKey[i].keyState = eKeyState::none; //none상태
				}
				mKey[i].pressCheck = false;
			}
		}
	}

	void keyInput::render(HDC hdc)
	{
	}
}