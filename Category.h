#pragma once

namespace Category
{
	enum Type
	{
		None				= 0,
		PlayerPiece			= 1 << 1,
		EnemyPiece			= 1 << 2,
		SoundEffect			= 1 << 3,
		Network				= 1 << 4,
	};
}