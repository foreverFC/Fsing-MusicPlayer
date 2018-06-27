#include "database.h"
#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <macro.h>
#include <sstream>
#include "macro.h"
#include "json/json.h"

using std::string;           using std::cout;
using std::endl;

DatabaseController::DatabaseController()
{
}

std::string DatabaseController::findUser(std::string username, std::string password)
{
    //姓名、密码正确返回SUCCESS
    //姓名正确、密码错误返回PW_INVALID
    //账户不存在NAME_INVALID

    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","mxy","mxy","mxy",3306,NULL,0)){
        cout << "findUser conect MYSQL failed!" << endl;
        return FAILD;
    }

    char sql[100];
    auto name = username.data();
//    auto pw = password.data();
    std::sprintf(sql,"select * from Account WHERE name= '%s'",name);
    size_t length =strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);
    if(res != 0){
        cout <<"fondUser select * from Account failed" << endl;
    }else{
        MYSQL_RES *result;
        MYSQL_ROW row;
        //    MYSQL_FIELD *fields;

        result = mysql_store_result(&mysql);
        if(result){
            while(row = mysql_fetch_row(result)){
                //                m_userNameFlag = true;
                if(string(row[2]) == password){
                    m_userName = row[1];
                    m_userPassword = row[2];
                    //                    m_userPassword = true;
                    return SUCCESS;
                }else
                    return PW_INVALID;
            }
        }
    }
    return NAME_INVALID;
    //    if(!m_userNameFlag){
    //        return USER_INVALID;
    //    }
}

std::string DatabaseController::myLogin(std::string username, std::string password)
{
    auto res =findUser(username,password);
    return res;
}
std::string DatabaseController::songInformation(std::string songSource)
{

    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","mxy","mxy","mxy",3306,NULL,0)){
        cout << "findUser conect MYSQL failed!" << endl;
        return FAILD;
    }

    char sql[100];
    auto source = songSource.data();
//    auto pw = password.data();
    std::sprintf(sql,"select * from songinfo WHERE source= '%s'",source);
    size_t length =strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);
    if(res != 0){
        cout <<"fondUser select * from Account failed" << endl;
    }else{
        MYSQL_RES *result;
        MYSQL_ROW row;
        //    MYSQL_FIELD *fields;

        result = mysql_store_result(&mysql);
        if(result){
            while(row = mysql_fetch_row(result)){
                //                m_userNameFlag = true;
                if(string(row[1]) == source){

                    std::string songName = row[0];
                    Json::Value root;
                    root["type"] = "SONGINFO";
                    root["songName"] = songName;
                    root.toStyledString();
                    std::string out = root.toStyledString();
                    return out.data();
            }
        }
    }
    }
    return "null infomation";
}

std::string DatabaseController::myRegister(std::string username, std::string password)
{
    //注册成功返回SUCCESS,反之返回FAILD
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","mxy","mxy","mxy",3306,NULL,0)){
        cout << "findUser conect MYSQL failed!" << endl;
        return FAILD;
    }

    //创建Account表
    hasAccountTable();

    auto ret = findUser(username,password);
    auto name = username.data();
    auto pw = password.data();
    if(ret == NAME_INVALID){
        auto maxid = getMaxid();
        char sql[100];
        std::sprintf(sql,"insert into Account(id,name,password) values('%d','%s','%s')",maxid,name,pw);
        auto length = strlen(sql);
        if(!mysql_real_query(&mysql,sql,length)){
            cout <<"create user " << username << " success " << endl;
            return SUCCESS;
        }
    }

    return FAILD;
}

int DatabaseController::getMaxid()
{
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","mxy","mxy","mxy",3306,NULL,0)){
        cout << "findUser conect MYSQL failed!" << endl;
        return 0;
    }
    string str{"select max(id) from Account"};
    auto length = str.size();
    mysql_real_query(&mysql,"select max(id) from Account",length);

    int maxid;
    MYSQL_RES *result;
    MYSQL_ROW row;
    result = mysql_store_result(&mysql);
    if(result){
        if(row = mysql_fetch_row(result)){
            string str = row[0];
            std::stringstream in(str);
            in >> maxid;
        }
    }

    return ++maxid;

}

void DatabaseController::hasAccountTable()
{
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","mxy","mxy","mxy",3306,NULL,0)){
        cout << "findUser conect MYSQL failed!" << endl;
        return;
    }

    //查找是否有Account表
    MYSQL_RES *result;
    MYSQL_ROW row;
    char sql1[100];
    std::sprintf(sql1,"show tables;");
    auto length1 = std::strlen(sql1);
    mysql_real_query(&mysql,sql1,length1);
    result = mysql_store_result(&mysql);
    if(result){
        while(row = mysql_fetch_row(result)){
            if(row[0] == "Account"){
                return;
            }
        }
    }

    //没有Account表，创建Account表
    string str{"CREATE TABLE Account("
               "id int NOT NULL AUTO_INCREMENT PRIMARY KEY,"
               "name char(20) not null,"
               "password char(20) not null);"};

    auto length = str.size();
    if(!mysql_real_query(&mysql,"CREATE TABLE Account("
                         "id int NOT NULL AUTO_INCREMENT PRIMARY KEY,"
                         "name char(20) not null,"
                         "password char(20) not null);",length)){
        cout <<"create table Account!" << endl;
    }
    mysql_query(&mysql,"insert into Account(id,name,password) values(1,'jack','1234');");
}

