
/*
 g++ -g myDataCache.cpp -I/usr/include/cppconn -L/usr/lib/cppconn -lmysqlcppconn -L/usr/lib/boost -lboost_thread -lpthread -o myDataCache1
*/
#include "myDataCache.h"
#include <pthread.h>
#include <unistd.h>
#include <sstream>
/*
#define BOOST_DATE_TIME_SOURCE
#define BOOST_THREAD_NO_LIB
#include <boost/thread.hpp>
*/
//using namespace boost;
#define BOOST_DATE_TIME_SOURCE
#define BOOST_THREAD_NO_LIB
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
using namespace boost;

Datacache::Datacache()
{
	driverxd = get_driver_instance();
	con_autoxd.reset(driverxd->connect("tcp://127.0.0.1:3306", "zero", "zerolove"));
	//conxd = driver->connect("tcp://127.0.0.1:3306", "zero", "zerolove");
	con_autoxd->setSchema("player");
	
	if(!con_autoxd.get())
	{
		std::cout<< "connect error "<< std::endl;
	}
	std::cout<<"constructing...datacache..."<<std::endl;
	stmt_autoxd.reset(con_autoxd->createStatement());
	boost::thread thrd_syn(boost::bind(&Datacache::syn_to_dbxd, this));
	thrd_syn.detach();
	std::cout << "connstruct OK ............";
}

Datacache::~Datacache()
{
	
}

void Datacache::syn_to_dbxd(void)
{
	string query_up;
	std::map<string,std::vector<player_info_struct> >::iterator itxd;
	std::vector<player_info_struct>::iterator uitxd;
	while(1)
	{
		sleep(5);
		std::cout<<"syn now..................."<<std::endl;
		itxd = player_mapxd.begin();
		while(itxd != player_mapxd.end())
		{
			sleep(5);
			std::cout<<"syn now 111111111.........."<<std::endl;
			//std::cout<<"syn now..................."<<std::endl;
			string update_user = itxd->first;
			uitxd = itxd->second.begin();
			
			//if  ins_seconds !=  updata_timexd ,update
			if(uitxd->ins_seconds != uitxd->updata_timexd)
			{
				stringstream idxdss,location_xxdss,location_yxdss,logo_idxdss,experiencesxdss;
				string idxd;
				string location_xxd;
				string location_yxd;
				string logo_idxd;
				string experiencesxd;
				string s("update user_info set ");
				string s1(" player_id=");
				string s2(", user_name=");
				string s3(" user_password=");
				string s4(", location_x=");
				string s5(", location_y=");
				string s6(", logo_id=");
				string s7(", e_mail=");
				string s8(", experiences=");
				string s9(" where user_name=");
				string sdo("\"");
				idxdss << uitxd->player_id;
				idxd = idxdss.str();
				
				location_xxdss << uitxd->location_x;
				location_xxd = location_xxdss.str();
				
				location_yxdss << uitxd->location_y;
				location_yxd = location_yxdss.str();
				
				logo_idxdss << uitxd->logo_id;
				logo_idxd = logo_idxdss.str();
				
				experiencesxdss << uitxd->experiences;
				experiencesxd = experiencesxdss.str();
				//UPDATE Person SET Address = 'Zhongshan 23', City = 'Nanjing' WHERE LastName = 'Wilson'
				query_up = s + s3 +sdo+uitxd->user_password+sdo + s4 \
				+ location_xxd + s5 + location_yxd + s6 + logo_idxd + s7 + sdo+uitxd->e_mail+sdo + s8 + \
				experiencesxd + s9 + sdo + update_user + sdo;
				
				std::cout<< query_up <<std::endl;
				stmt_autoxd->executeQuery(query_up);
			}
			++itxd;
		}
	}
}

status Datacache::update_to_dbxd()
{
	
	return SUCCESS;
}

void Datacache::mylru()
{
	time_t inser_time;
	std::map<string,std::vector<player_info_struct> >::iterator player_mapxd_iter;
	player_mapxd_iter = player_mapxd.begin();
	std::map<string,std::vector<player_info_struct> >::iterator erase_map;
	erase_map = player_mapxd.begin();
	
	std::vector<player_info_struct>::iterator itxd;
	itxd = player_mapxd_iter->second.begin();
	
	inser_time = itxd->ins_seconds;
	while(player_mapxd_iter != player_mapxd.end())
	{
		if(itxd->ins_seconds < inser_time)
		{
			inser_time = itxd->ins_seconds;
			erase_map = player_mapxd_iter;
		}
		++player_mapxd_iter;
	}
	/*
	std::map<string,std::vector<player_info_struct> >::iterator itxd = player_mapxd.find(user_nmxd);
		std::vector<player_info_struct>::iterator uitxd;
		if(itxd != player_mapxd.end())
		{
			uitxd = itxd->second.begin();
			for(;uitxd != itxd->second.end();)
			{
				std::cout << uitxd->player_id << "\t" << uitxd->user_namexd << "\t" << uitxd->user_password <<"\t"\
				<< uitxd->e_mail <<"\t" << uitxd->logo_id << "\t" << uitxd->location_x <<"\t" << uitxd->location_y <<"\t"\
				<<uitxd->experiences <<std::endl;
				uitxd++;
			}
	*/
	//erase map
	player_mapxd.erase(erase_map);
}
status Datacache::find_from_dbxd(string &user_nmxd)
{
	int flag = -1;
	status issuccess = SUCCESS;
	//sprintf(queryxd, "select * from user_info where user_name=\"%s\" ", user_nmxd);
	string half_queryxd1("select * from user_info where user_name=");
	string half_queryxd2("\"");
	string half_queryxd3("\"");
	queryxd = half_queryxd1 + half_queryxd2 + user_nmxd + half_queryxd3;
	std::cout<< queryxd <<std::endl;
	//res = stmt_autoxd->executeQuery(query);
	res_autoxd.reset(stmt_autoxd->executeQuery(queryxd));
		//create map and story to memory
		//取得结果集
		while (res_autoxd->next())
		{
			flag = 0;
			// You can use either numeric offsets...
			/*std::cout << "player_id = " << res_autoxd->getInt(1); // getInt(1) returns the first column
			std::cout << "\t user_namexd = '" << res_autoxd->getString("user_name") << "'";
			std::cout << "\t user_password = '" << res_autoxd->getString("user_password") << "'";
			std::cout << "\t location_x = '" << res_autoxd->getInt(4) << "'";
			std::cout << "\t location_y = '" << res_autoxd->getInt(5) << "'";
			std::cout << "\t logo_id = '" << res_autoxd->getInt(6) << "'";
			std::cout << "\t e_mail = '" << res_autoxd->getString("e_mail") << "'";
			std::cout << "\t experiences = '" << res_autoxd->getInt(8) << "'" << std::endl;
			*/
			//assign every val
			
			pis.player_id=res_autoxd->getInt(1);//atoi(res_autoxd->getInt(1));
			pis.user_namexd=res_autoxd->getString("user_name") ;//getInt(2);
			pis.user_password=res_autoxd->getString("user_password");//getInt(3);
			pis.location_x=res_autoxd->getInt(4);//atoi(res_autoxd->getInt(4));
			pis.location_y=res_autoxd->getInt(5);//atoi(res_autoxd->getInt(5));
			pis.logo_id=res_autoxd->getInt(6);//atoi(res_autoxd->getInt(6));
			pis.e_mail=res_autoxd->getString("e_mail");//getInt(7);
			pis.experiences=res_autoxd->getInt(8);//atoi(res_autoxd->getInt(8));
			pis.ins_seconds=time (NULL);
			pis.updata_timexd = pis.ins_seconds;
			player_infoxd.push_back(pis);//insert info into vector
			
		}
		//判断缓存的数据项是否超过50项
		if (player_mapxd.size()>=50)
		{
			//LRU
			mylru();
		}
		//把数据放入缓存中
		player_mapxd.insert(pair<string,vector<player_info_struct> >(user_nmxd,player_infoxd));
		//释放vector容器
		//player_infoxd.clear();
		//释放结果集
		//mysql_free_result(res);
		printf("cout all fields......\n");
		if(flag = -1)
		issuccess = FAILD
	return issuccess;
}

void Datacache::find_testxd()
{
	string myname("xie");
	find_from_dbxd(myname);
}


status Datacache::find_userxd(string user_nmxd)
{
	status issucc = SUCCESS;
	if(player_mapxd.find(user_nmxd)==player_mapxd.end())
	{
		std::cout << "user's info not in cache ,now selete from the db..."<<std::endl;
		
		issucc = find_from_dbxd(user_nmxd);//if user not register,return faild.
		if(issucc != 0)
			std::cout<<"user not here..." << std::endl;
	}
	else
	{
		std::cout<< "user's info in the cache..."<<std::endl<<"The user info below this line:"<<std::endl;
		std::map<string,std::vector<player_info_struct> >::iterator itxd = player_mapxd.find(user_nmxd);
		std::vector<player_info_struct>::iterator uitxd;
		if(itxd != player_mapxd.end())
		{
			string xxx = itxd->first;
			std::cout<< xxx <<"....."<<std::endl;
			std::cout<< "user infomation 00000.............."<<std::endl;
			uitxd = itxd->second.begin();
			for(;uitxd != itxd->second.end();)
			{
				std::cout<< "user infomation  1111111111.............."<<std::endl;
				std::cout << uitxd->player_id << "\t" << uitxd->user_namexd << "\t" << uitxd->user_password <<"\t"\
				<< uitxd->e_mail <<"\t" << uitxd->logo_id << "\t" << uitxd->location_x <<"\t" << uitxd->location_y <<"\t"\
				<<uitxd->experiences <<std::endl;
				uitxd++;
			}
		}
		/*
		 * */
	}//else
	return issucc;
}

//在memcache更新，没有更新到数据库，而是使用syn_to_dbxd函数同步到数据库，
status Datacache::update_uinfoxd()
{
	return update_to_dbxd();
}
void test_dc()
{
	
}
void Datacache::entry4thrd()
{
	
}
int main()
{
	Datacache dcxd;
	dcxd.find_testxd();
	string myname("xie");
	dcxd.find_userxd(myname);
	dcxd.find_userxd(myname);
	
	while(1)
	{
		sleep(4);
		std::cout << "xxxxxxxxxxxxxxxxxx"<<std::endl;
	}
	
	return EXIT_SUCCESS;
}
