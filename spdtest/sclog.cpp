#include "sclog.h"

using namespace std;

log::log(const std::string& logger_name)
{
	if (file_logger)
	{
		file_logger = nullptr;
	}
		try
	{
		std::vector<spdlog::sink_ptr> sinks;
		sinks.push_back(std::make_shared<spdlog::sinks::msvc_sink_mt>());
		sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(file_name, 1024 * 1024 * 4, 1));
		file_logger = std::make_shared<spdlog::logger>(file_name, begin(sinks), end(sinks));
		file_logger->set_pattern("[%Y-%m-%d %H:%M:%S] %v");
		file_logger->set_level(spdlog::level::trace);
		file_logger->info("======== init_log ========");
	}
	catch (...)
	{
		file_logger = nullptr;
	}
	 file_logger = spdlog::rotating_logger_mt("file_logger", _filename, _max_file_size, _max_files);
}
log::log(const size_t max_file_size) :_max_file_size(max_file_size)
{
	file_logger = spdlog::rotating_logger_mt("file_logger", _filename, _max_file_size, _max_files);
}
