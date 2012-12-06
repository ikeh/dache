#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <memory>
#include <ctime>

#define SUCCESS 0;
#define FAILD -1;
typedef unsigned int status;
using namespace std;
using std::string;

/*********************************************************/
typedef struct info player_info_struct;
struct info
{
	int player_id;
	string user_namexd;
	string user_password;
	int location_x;
	int location_y;
	int logo_id;
	string e_mail;
	int experiences;
	time_t ins_seconds;
	time_t updata_timexd;
};

class Datacache
{
	public:
		Datacache();
		~Datacache();
		status update_uinfoxd(); //updata from memory to db
		status find_userxd(string user_nmxd);//find from memory
		void find_testxd();
		
		void syn_to_dbxd(void);//it will syn data from memory to db with one minute
		void entry4thrd();
		
	private:
		status update_to_dbxd();//
		status find_from_dbxd(string &user_nmxd);//if user not in the memory find_user will call it
		
		void mylru();
		std::map<string,std::vector<player_info_struct> > player_mapxd;//user_name,player_info-struct
		//mymap player_mapxd;
		std::vector<player_info_struct> player_infoxd;//it is the real place to place the data
		
		//MYSQL connxd;
		//MYSQL_ROW rowxd;
		//MYSQL_RES *resxd;
		sql::Driver *driverxd;
		sql::Connection *conxd;
		std::auto_ptr<sql::Connection> con_autoxd;
		std::auto_ptr< sql::ResultSet > res_autoxd;
		std::auto_ptr< sql::Statement > stmt_autoxd;
		
		sql::Statement *stmtxd;
		sql::ResultSet *resxd;
		sql::PreparedStatement *pstmtxd;
		
		player_info_struct pis;
		string queryxd;
		
};

//不被嘲笑的梦想，是不值得被实现的
