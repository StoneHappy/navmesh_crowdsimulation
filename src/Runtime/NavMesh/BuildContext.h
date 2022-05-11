#pragma once
#include <Recast.h>
namespace Stone
{
	class BuildContext : public rcContext
	{
	public:

	protected:
		/// Logs a message.
		///  @param[in]		category	The category of the message.
		///  @param[in]		msg			The formatted message.
		///  @param[in]		len			The length of the formatted message.
		virtual void doLog(const rcLogCategory /*category*/, const char* /*msg*/, const int /*len*/) override;
	private:

	};
}