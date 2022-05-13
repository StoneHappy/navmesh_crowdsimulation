#pragma once
#include <Resource/Data/Implement/VCG/VCGMesh.h>
#include <vector>
namespace Stone
{
	class NavGeoMesh : public VCGMesh
	{
	public:
		NavGeoMesh(const std::string& filename);

		const float* getBoundsMin();
		const float* getBoundsMax();
		const float* getVerts();
		const int getVertCount();
		const int* getTris();
		const int getTriCount();

	private:
		std::vector<float> m_Points;
		std::vector<int> m_Tris;
	};
}