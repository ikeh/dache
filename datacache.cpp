
#include <datacache.h>
#include <mysql/mysql.h>

Datacache::Datacache()
{
	mysql_init(&connection);
	if(mysql_real_connect(&connection, "localhost", "zero", "zerolove", "player", 3306, NULL, 0) == NULL)
	{
		std::cout<< "connect error "<< mysql_error(&connection)<< std::endl;
	}
	mysql_set_character_set(&connection, "utf8");
}

Datacache::~Datacache(){}

status find_user(string user_name)
{
}
