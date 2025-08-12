#include <Windows.h>
#include <iostream>
#include "players.h"
#include <vector>
#include <algorithm>
using namespace std;


CHackProcess fProcess;
using namespace std;

#define F6_Key 0x75
#define RIGHT_MOUSE 0x02

int NumOfPlayers = 32;

const DWORD dw_PlayerCountOffs = 0x5EF6BC;
const DWORD Player_Base = 0x4C6708;
const DWORD dw_m_angRotation = 0x47F1B4;

const DWORD dw_mTeamOffset = 0x9C;
const DWORD dw_Health = 0x94;
const DWORD dw_Pos = 0x260;

const DWORD EntityPlayer_Base = 0x4D3904;
const DWORD EntityLoopDistance = 0x10;

struct MyPlayer_t
{
	DWORD CLocalPlayer;
	int Team;
	int Health;
	float Position[3];
	void ReadInformation()
	{
		ReadProcessMemory(fProcess.__HandleProcess, (BYTE*)(fProcess.__dwordClient + Player_Base), &CLocalPlayer, sizeof(CLocalPlayer), 0);
		ReadProcessMemory(fProcess.__HandleProcess, (BYTE*)(CLocalPlayer + dw_mTeamOffset), &Team, sizeof(Team), 0);
		ReadProcessMemory(fProcess.__HandleProcess, (BYTE*)(CLocalPlayer + dw_Health), &Health, sizeof(Health), 0);
		ReadProcessMemory(fProcess.__HandleProcess, (BYTE*)(CLocalPlayer + dw_Pos), &Position, sizeof(float[3]), 0);
		ReadProcessMemory(fProcess.__HandleProcess, (BYTE*)(fProcess.__dwordEngine + dw_PlayerCountOffs), &NumOfPlayers, sizeof(int), 0);
	}
}MyPlayer;

struct TargetList_t
{
	float Distance;
	float AimbotAngle[3];

	TargetList_t() {}

	TargetList_t(float aimbotAngle[], float myCoords[], float enemyCoords[])
	{
		Distance = Get3dDistance(myCoords[0], myCoords[1], myCoords[2],
			enemyCoords[0], enemyCoords[1], enemyCoords[2]);

		AimbotAngle[0] = aimbotAngle[0];
		AimbotAngle[1] = aimbotAngle[1];
		AimbotAngle[2] = aimbotAngle[2];
	}

	float Get3dDistance(float myCoordsX, float myCoordsZ, float myCoordsY,
		float eNx, float eNz, float eNy)
	{
		return (float)sqrt(
			pow(double(eNx - myCoordsX), 2.0) +
			pow(double(eNy - myCoordsY), 2.0) +
			pow(double(eNz - myCoordsZ), 2.0));
	}
};

struct PlayerList_t
{
	DWORD CBaseEntity;
	int Team;
	int Health;
	float Position[3];
	float AimbotAngle[3];
	char Name[39];

	void ReadInformation(int Player)
	{
		ReadProcessMemory(fProcess.__HandleProcess, (BYTE*)(fProcess.__dwordClient + EntityPlayer_Base + (Player * EntityLoopDistance)), &CBaseEntity, sizeof(DWORD), 0);
		ReadProcessMemory(fProcess.__HandleProcess, (BYTE*)(CBaseEntity + dw_mTeamOffset), &Team, sizeof(int), 0);
		ReadProcessMemory(fProcess.__HandleProcess, (BYTE*)(CBaseEntity + dw_Health), &Health, sizeof(int), 0);
		ReadProcessMemory(fProcess.__HandleProcess, (BYTE*)(CBaseEntity + dw_Pos), &Position, sizeof(float[3]), 0);
	}
}PlayerList[32];

struct CompareTargetEnArray
{
	bool operator() (TargetList_t& lhs, TargetList_t& rhs)
	{
		return lhs.Distance < rhs.Distance;
	}
};

void CalcAngle(float* src, float* dst, float* angles)
{
	double delta[3] = { (src[0] - dst[0]), (src[1] - dst[1]), (src[2] - dst[2]) };
	double hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
	angles[0] = (float)(asinf(delta[2] / hyp) * 57.295779513082f);
	angles[1] = (float)(atanf(delta[1] / delta[0]) * 57.295779513082f);
	angles[2] = 0.0f;

	if (delta[0] >= 0.0)
	{
		angles[1] += 180.0f;
	}
}

void Aimbot()
{
	TargetList_t* TargetList = new TargetList_t[NumOfPlayers];

	int targetLoop = 0;
	for (int i = 0; i < NumOfPlayers; i++)
	{
		PlayerList[i].ReadInformation(i);

		if (PlayerList[i].Team == MyPlayer.Team) continue;

		if (PlayerList[i].Health < 2) continue;

		CalcAngle(MyPlayer.Position, PlayerList[i].Position, PlayerList[i].AimbotAngle);

		TargetList[targetLoop] = TargetList_t(PlayerList[i].AimbotAngle, MyPlayer.Position, PlayerList[i].Position);

		targetLoop++;
	}

	if (targetLoop > 0)
	{
		std::sort(TargetList, TargetList + targetLoop, CompareTargetEnArray());

		if (!GetAsyncKeyState(0x2))
		{
			WriteProcessMemory(fProcess.__HandleProcess, (BYTE*)(fProcess.__dwordEngine + dw_m_angRotation), TargetList[0].AimbotAngle, 12, 0);
		}

	}
	targetLoop = 0;

	delete[] TargetList;
}

int main()
{
	fProcess.RunProcess();
	cout << "Game found! Running b00m h3adsh0t aimbot." << endl;

	while (!GetAsyncKeyState(F6_Key))
	{
		MyPlayer.ReadInformation();
		Aimbot();
	}
}
