#include "NavGeoMesh.h"
namespace Stone
{
	NavGeoMesh::NavGeoMesh(const std::string& filename)
		: VCGMesh(filename)
	{
		m_Points.reserve(m_Mesh.VN());
		for (auto& v : m_V)
		{
			m_Points.push_back(v.px);
			m_Points.push_back(v.py);
			m_Points.push_back(v.pz);
		}
		for (auto& face : m_Mesh.face)
		{
			if (!face.IsD())
			{
				for (size_t i = 0; i < 3; i++)
				{
					m_Tris.push_back(vcg::tri::Index(m_Mesh, face.V(i)));
				}
			}
		}
		
	}
	const float* NavGeoMesh::getBoundsMin()
	{
		return (float*)&m_Mesh.bbox.min;
	}
	const float* NavGeoMesh::getBoundsMax()
	{
		return (float*)&m_Mesh.bbox.max;
	}
	const float* NavGeoMesh::getVerts()
	{
		return m_Points.data();
	}
	const int NavGeoMesh::getVertCount()
	{
		return m_Mesh.VN();
	}
	const int* NavGeoMesh::getTris()
	{
		return m_Tris.data();
	}
	const int NavGeoMesh::getTriCount()
	{
		return m_Mesh.FN();
	}
}