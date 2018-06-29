#include "fsingservice.h"
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include "database.h"
#include "macro.h"
#include "json/json.h"

using namespace boost::asio;
using std::cout;            using std::endl;
using std::string;          using std::vector;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;


io_service service;   //创建调度器
ip::tcp::endpoint ep(ip::tcp::v4(),2001);  //监听端口
ip::tcp::acceptor acc(service,ep); //创建连接器
DatabaseController database;

vector<std::string> jsonParase(char data[]);
//接受客户端传来的请求事务,并将结果返回给客户端
void receiveMessage(socket_ptr sock);
//返回处理信息给客户端
void dealResult(socket_ptr sock);


Server::Server()
{
}

void Server::connect()
{
    //如果套接字连接一个已经在使用中的本地地址，则进行重用地址，因为每一个连接都由本地地址和远端地址的组合唯一确定，所以只要远端地址不同，两个套接口与一个地址捆绑并无大碍
    //设置套接口实现不要因为一个地址已被一个套接口使用就不让它与另一个套接口捆绑，在bind()调用前先设置SO_REUSEADDR选项
//    ip::tcp::socket sock_;
    bool value = true;
    setsockopt(1,SOL_SOCKET,SO_REUSEADDR,(void *)&value,sizeof(value));
    while(true){
        socket_ptr sock(new ip::tcp::socket(service));
        acc.accept(*sock); //接收新的连接
        boost::thread(boost::bind(receiveMessage,sock)); //开辟线程去处理该连接上的事务
        //前两步可以等价于
        //        acc.async_accept(*sock,boost::bind(client_session,sock));
    }
}


string Server::dealMessage(string sig,vector<string> str,socket_ptr sock)
{
    string res;
    if(sig == "SONGINFO"){
        res = database.songInformation(str[1]);
        return res;
    }else if(sig == "REGISTER"){
        res = database.myRegister(str[1],str[2]);
        return res;
    }else if(sig == "LOGIN"){
        res = database.myLogin(str[1],str[2]);
        return res;
    }else if(sig == "SEARCH"){
        res = database.search(str[1]);
        return res;
    }else if(sig == "FILETRANSFER"){
        fileSender(str[1],sock);
        res = "fileTransfer";
        return res;
    }
    return "nomatch sig";
}

//接受客户端传来的请求事务,并将结果返回给客户端
void receiveMessage(socket_ptr sock)
{
    //    auto ep = sock->remote_endpoint();//获得客户端的连接端口
    boost::system::error_code ec;
    auto ep1 = sock->remote_endpoint(ec); //获得客户端的连接端口
    if(ec)
    {
        std::cout << boost::system::system_error(ec).what() << std::endl;
    }
    std::cout<<ep1.address().to_string()<<"连接"<<std::endl;

    Server service;
    while(true)
    {
        char data1[512];
        memset(data1,0,sizeof(char)*512);

        DatabaseController database;
        /*auto len = */sock->read_some(buffer(data1), ec);
        if(ec)
        {
            std::cout << boost::system::system_error(ec).what() << std::endl;
            break;
        }
        cout << "receive from client : " << data1<<endl;

        auto result1 = jsonParase(data1);
        auto result2 = service.dealMessage(result1[0],result1,sock);

        if(result2 == "fileTransfer"){
            cout << "transfer finished" << endl;
            return;
        }
        //写回客户端
        char data2[512];
        memset(data2,0,sizeof(char)*512);
        result2.copy(data2,result2.size(),0);
        sock->write_some(buffer(data2), ec);  //客户输入的消息，重新写到客户端
        if(ec)
        {
            std::cout << boost::system::system_error(ec).what() << std::endl;
            break;
        }
        cout << "send to client : " << data2<<endl;

    }
    std::cout<<ep1.address().to_string()<<"关闭"<<std::endl;
}

vector<string>  jsonParase(char data[]){
    vector<string>  parameter;
    Json::Value value;
    Json::Reader reader;
    if (!reader.parse(data, value))
    {
        cout << "receive from client failed" <<endl;
    }else{
        string type = value["type"].asString();
        if(type == "SONGINFO"){
            parameter.push_back(value["type"].asString());
            parameter.push_back(value["songInfo"].asString());
        }else if(type == "REGISTER"){
            parameter.push_back(value["type"].asString());
            parameter.push_back(value["userName"].asString());
            parameter.push_back(value["userPassword"].asString());
        }else if(type == "LOGIN"){
            parameter.push_back(value["type"].asString());
            parameter.push_back(value["userName"].asString());
            parameter.push_back(value["userPassword"].asString());
        }else if(type == "SEARCH"){
            parameter.push_back(value["type"].asString());
            parameter.push_back(value["songKey"].asString());
        }else if(type == "FILETRANSFER"){
            parameter.push_back(value["type"].asString());
            parameter.push_back(value["fileName"].asString());
        }
        }
    return parameter;
}
void Server::fileSender(string fileName,socket_ptr sock){
    typedef boost::asio::ip::tcp TCP;

    auto filename = fileName.data();
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
      cout << "cannot open file\n" <<endl;;
      return;
    }

    //使用智能指针，防止程序出现异常时，fclose未被调用。
    boost::shared_ptr<FILE> file_ptr(fp, fclose);

    clock_t cost_time = clock();

    const size_t k_buffer_size = 32 * 1024;
    char buffer[k_buffer_size];
    File_info file_info;

    int filename_size  = strlen(filename) + 1;
    size_t file_info_size = sizeof(file_info);
    size_t total_size = file_info_size + filename_size;
    if (total_size > k_buffer_size) {
      std::cerr << "File name is too long";
      return;
    }
    file_info.filename_size = filename_size;

    fseek(fp, 0, SEEK_END);
    file_info.filesize = ftell(fp);
    rewind(fp);

    memcpy(buffer, &file_info, file_info_size);
    memcpy(buffer + file_info_size, filename, filename_size);


    std::cout << "Sending file : " << filename << "\n";
    size_t len = total_size;
    unsigned long long total_bytes_read = 0;
    while (true) {
      sock->send(boost::asio::buffer(buffer, len), 0);
      if (feof(fp)) break;
      len = fread(buffer, 1, k_buffer_size, fp);
      total_bytes_read += len;
    }

    cost_time = clock() - cost_time;
    if (cost_time == 0) cost_time = 1;
    double speed = total_bytes_read * (CLOCKS_PER_SEC / 1024.0 / 1024.0) / cost_time;
    std::cout << "cost time: " << cost_time / (double) CLOCKS_PER_SEC  << " s "
      << "  transferred_bytes: " << total_bytes_read << " bytes\n"
      << "speed: " <<  speed << " MB/s\n\n";
}

void dealResult(socket_ptr sock){}
