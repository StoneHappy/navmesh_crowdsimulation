#pragma once
#include <Recast.h>
#include <Core/Base/PublicSingleton.h>

#include "BuildContext.h"

#include <Resource/Data/Implement/VCG/VCGMesh.h>

#include "NavGeoMesh.h"
namespace Stone
{
	class NavMeshSample : PublicSingleton<NavMeshSample>
	{
	public:
		NavMeshSample();

		void attachMesh(NavGeoMesh* mesh);
		bool handelBuild();

	private:
		void spansToScene();

		NavGeoMesh* m_Mesh = nullptr;
		rcHeightfield* m_solid;
		BuildContext* m_ctx;
		rcConfig m_cfg;
		unsigned char* m_triareas;

		float m_cellSize = 0.3;
		float m_cellHeight = 0.2;
		float m_agentHeight  = 2.0;
		float m_agentRadius = 0.6;
		float m_agentMaxClimb = 0.9;
		float m_agentMaxSlope = 45;
		float m_regionMinSize = 8;
		float m_regionMergeSize = 20;
		float m_edgeMaxLen = 12;
		float m_edgeMaxError = 1.3;
		float m_vertsPerPoly;
		float m_detailSampleDist;
		float m_detailSampleMaxError;
		int m_partitionType;
	};
}