
typedef enum
{
	trace = 0,
	debug = 1,
	info = 2,
	warn = 3,
	err = 4,
	critical = 5,
	off = 6
} level_enum;
typedef enum
{
	module1 = 0,
	module2 = 1,
	module3 = 2,
	module4 = 3,
	module5 = 4,
	module6 = 5,
	module7 = 6
} module_enum;

class sclog
{
public:
	sclog();//start sclog & use default max size = 1024 * 1024 * 1,max files = 7 
	sclog(size_t max_file_size, size_t max_files);//start sclog & use the max_file_size,max_files
	sclog(size_t max_file_size, level_enum log_level);//set log level to all loggers to the level and above
	void write(module_enum mod, level_enum lvl, const char* msg);
	template<typename T>
	void write(module_enum mod, level_enum lvl, const T& msg);//const char *format, ...);
	//log(module2, warn, "hello NO:" + tmptest + "..");
	void read();
	
};


