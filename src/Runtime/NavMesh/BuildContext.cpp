#include "BuildContext.h"
#include <Core/Base/macro.h>
namespace Stone
{
	void BuildContext::doLog(const rcLogCategory logcategory, const char* msg, const int len)
	{
		if (len == 0)return;
		switch (logcategory)
		{
		case RC_LOG_PROGRESS:
			LOG_INFO(msg);
			break;
		case RC_LOG_WARNING:
			LOG_WARN(msg);
			break;
		case RC_LOG_ERROR:
			LOG_ERROR(msg);
			break;
		default:
			break;
		}
	}
}