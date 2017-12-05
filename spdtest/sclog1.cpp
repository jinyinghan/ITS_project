#include "sclog1.h"
namespace hik
{
	log::log()
	{
		file_logger = spdlog::daily_logger_mt("daily_logger", "daily", 0, 1);
	}
	
		template < typename... Args>
		static void log::trace(const std::string& module, const char* fmt, Args&&... args)
		{
			file_logger->spdlog::trace(fmt,args);
		}

		template < typename... Args>
		void log::debug(const std::string& module, const char* fmt, Args&&... args);

		template < typename... Args>
		void log::info(const std::string& module, const char* fmt, Args&&... args);

		template < typename... Args>
		void log::warn(const std::string& module, const char* fmt, Args&&... args);

		template < typename... Args>
		void log::error(const std::string& module, const char* fmt, Args&&... args);

		template< typename... Args>
		void log::fatal(const std::string& module, const char* fmt, Args&&... args);

}
