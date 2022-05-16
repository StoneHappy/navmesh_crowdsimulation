#include "NavMeshSample.h"
#include <Core/Base/macro.h>
#include <glm/glm.hpp>
namespace Stone
{
	NavMeshSample::NavMeshSample()
	{
		m_ctx = new BuildContext();
	}
	void NavMeshSample::attachMesh(NavGeoMesh* mesh)
	{
		m_Mesh = mesh;
	}
	bool NavMeshSample::handelBuild()
	{
		if (m_Mesh == nullptr) return false;

		const float* bmin = m_Mesh->getBoundsMin();
		const float* bmax = m_Mesh->getBoundsMax();
		const float* verts = m_Mesh->getVerts();
		const int nverts = m_Mesh->getVertCount();
		const int* tris = m_Mesh->getTris();
		const int ntris = m_Mesh->getTriCount();

		//
		// Step 1. Initialize build config.
		//

		// Init build configuration from GUI
		memset(&m_cfg, 0, sizeof(m_cfg));
		m_cfg.cs = m_cellSize;
		m_cfg.ch = m_cellHeight;
		m_cfg.walkableSlopeAngle = m_agentMaxSlope;
		m_cfg.walkableHeight = (int)ceilf(m_agentHeight / m_cfg.ch);
		m_cfg.walkableClimb = (int)floorf(m_agentMaxClimb / m_cfg.ch);
		m_cfg.walkableRadius = (int)ceilf(m_agentRadius / m_cfg.cs);
		m_cfg.maxEdgeLen = (int)(m_edgeMaxLen / m_cellSize);
		m_cfg.maxSimplificationError = m_edgeMaxError;
		m_cfg.minRegionArea = (int)rcSqr(m_regionMinSize);		// Note: area = size*size
		m_cfg.mergeRegionArea = (int)rcSqr(m_regionMergeSize);	// Note: area = size*size
		m_cfg.maxVertsPerPoly = (int)m_vertsPerPoly;
		m_cfg.detailSampleDist = m_detailSampleDist < 0.9f ? 0 : m_cellSize * m_detailSampleDist;
		m_cfg.detailSampleMaxError = m_cellHeight * m_detailSampleMaxError;

		// Set the area where the navigation will be build.
		// Here the bounds of the input mesh are used, but the
		// area could be specified by an user defined box, etc.
		rcVcopy(m_cfg.bmin, bmin);
		rcVcopy(m_cfg.bmax, bmax);
		rcCalcGridSize(m_cfg.bmin, m_cfg.bmax, m_cfg.cs, &m_cfg.width, &m_cfg.height);

		LOG_DEBUG("width: {0}", m_cfg.width, m_cfg.height);
		// Reset build times gathering.
		m_ctx->resetTimers();

		// Start the build process.	
		m_ctx->startTimer(RC_TIMER_TOTAL);

		m_ctx->log(RC_LOG_PROGRESS, "Building navigation:");
		m_ctx->log(RC_LOG_PROGRESS, " - %d x %d cells", m_cfg.width, m_cfg.height);
		//m_ctx->log(RC_LOG_PROGRESS, " - %.1fK verts, %.1fK tris", nverts / 1000.0f, ntris / 1000.0f);
		m_ctx->log(RC_LOG_PROGRESS, " - %d verts, %d tris", nverts, ntris);

		//
		// Step 2. Rasterize input polygon soup.
		//

		// Allocate voxel heightfield where we rasterize our input data to.
		m_solid = rcAllocHeightfield();
		if (!m_solid)
		{
			m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'solid'.");
			return false;
		}
		if (!rcCreateHeightfield(m_ctx, *m_solid, m_cfg.width, m_cfg.height, m_cfg.bmin, m_cfg.bmax, m_cfg.cs, m_cfg.ch))
		{
			m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not create solid heightfield.");
			return false;
		}

		// Allocate array that can hold triangle area types.
		// If you have multiple meshes you need to process, allocate
		// and array which can hold the max number of triangles you need to process.
		m_triareas = new unsigned char[ntris];
		if (!m_triareas)
		{
			m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'm_triareas' (%d).", ntris);
			return false;
		}

		// Find triangles which are walkable based on their slope and rasterize them.
		// If your input data is multiple meshes, you can transform them here, calculate
		// the are type for each of the meshes and rasterize them.
		memset(m_triareas, 0, ntris * sizeof(unsigned char));
		rcMarkWalkableTriangles(m_ctx, m_cfg.walkableSlopeAngle, verts, nverts, tris, ntris, m_triareas);
		if (!rcRasterizeTriangles(m_ctx, verts, nverts, tris, m_triareas, ntris, *m_solid, m_cfg.walkableClimb))
		{
			m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not rasterize triangles.");
			return false;
		}

		spansToScene();
		return true;
	}
	void NavMeshSample::spansToScene()
	{
		int spancount = 0;
		for (size_t i = 0; i < m_cfg.width; i++)
		{
			for (size_t j = 0; j < m_cfg.height; j++)
			{
				spancount++;
			}
		}

		LOG_DEBUG("spancount: {0}", spancount);
	}
}