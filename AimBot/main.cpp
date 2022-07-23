#include"memory.h"
#include"Vector.h"
#include<thread>

namespace offset
{
	//client
	constexpr ::std::ptrdiff_t dwLocalPlayer = 0xDA746C;
	constexpr ::std::ptrdiff_t dwEntitList = 0x4DC178C;

	//engine
	constexpr ::std::ptrdiff_t dwClientState = 0x589FCC;
	constexpr ::std::ptrdiff_t dwClientState_ViewAngles = 0x4D90;

	//entity
	constexpr ::std::ptrdiff_t m_dwBoneMatrix = 0x26A8;
	constexpr ::std::ptrdiff_t m_bDormant = 0xED;
	constexpr ::std::ptrdiff_t m_iTeamNum = 0xF4;
	constexpr ::std::ptrdiff_t m_iHealth = 0x100;
	constexpr ::std::ptrdiff_t m_vecOrigin = 0x138;
	constexpr ::std::ptrdiff_t m_vecViewOffset = 0x108;
	constexpr ::std::ptrdiff_t m_aimPunchAngle = 0x303C;
	constexpr ::std::ptrdiff_t m_bSpottedByMask = 0x980;

}

constexpr Vector3 CalculateAngle(
	const Vector3& localPosition,
	const Vector3& enemyPosition,
	const Vector3& viewAngles) noexcept
{
	return ((enemyPosition - localPosition).ToAngle() - viewAngles);
}





int main()
{
	//initialize memory class 
	const auto memory = Memory{"csgo.xe"};

	const auto client = memory.GetModuleAddress("client.dll");
	const auto engine = memory.GetModuleAddress("engine.dll");


	// inifinite hack loop
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(1));

		//aimbot hotkey : RBUTTON
		if (!GetAsyncKeyState(VK_RBUTTON))
			continue;

		//get local player
		const auto& localPlayer = memory.Read<std::uintptr_t>(client + offset::dwLocalPlayer);
		const auto& localTeam = memory.Read<std::int32_t>(localPlayer + offset::m_iTeamNum);

		// eye position = origin + viewOffeset
		const auto localEyePosition = memory.Read<Vector3>(localPlayer + offset::m_vecOrigin) +
			memory.Read<Vector3>(localPlayer + offset::m_vecViewOffset);
	}


	return 0;
}