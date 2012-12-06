#include <iostream>
#include <map>
#include <vector>
#include <string>
typedef unsigned int status
#define SUCCESS 0;
#define FAILD -1;

typedef struct info
{
	int player_id;
	string user_name;
	string user_password;
	int location_x;
	int location_y;
	int logo_id;
	string e_mail;
	int experiences;
}player_info_struct;

class Datacache
{
	public:
		status update_uinfo();
		status find_user(string user_name);
		Datacache();
		~Datacache();

	private:
		status update_to_db();
		status find_from_db();
		status syn_to_db();
		std::map<string,std::vector<player_info_struct> > player_map;
		std::vector<player_info_struct> player_info;
		player_info_struct pis;
		MYSQL connection;
}
