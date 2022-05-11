#pragma once
#include <Recast.h>
#include <Core/Base/PublicSingleton.h>

#include "BuildContext.h"
namespace Stone
{
	class NavMeshSample : PublicSingleton<NavMeshSample>
	{
	public:
		NavMeshSample();
		void handelBuild();
	private:
		rcHeightfield* m_solid;
		BuildContext* m_ctx;
	};
}