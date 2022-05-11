#include "NavMeshSample.h"
#include <Core/Base/macro.h>
#include <glm/glm.hpp>
namespace Stone
{
	NavMeshSample::NavMeshSample()
	{
		m_ctx = new BuildContext();
	}
	void NavMeshSample::handelBuild()
	{
		m_solid = rcAllocHeightfield();
		glm::vec3 min = glm::vec3(0);
		glm::vec3 max = {100, 100, 100};
		ASSERT(m_solid, "buildNavigation: Out of memory 'solid'.");
		ASSERT(rcCreateHeightfield(m_ctx, *m_solid, 100, 100, (float*)&min,(float*)&max, 10, 10), "buildNavigation: Could not create solid heightfield.");
	}
}