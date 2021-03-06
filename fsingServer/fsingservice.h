#ifndef FSINGSERVICE_H
#define FSINGSERVICE_H

#include <boost/asio.hpp>
#include <string>
#include <memory>
#include "fanbroker.h"
#include <songlistbroker.h>
#include <songbroker.h>
#include "database.h"
#include "fanproxy.h"
#include "songlistproxy.h"
#include "songproxy.h"

using std::vector;
typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

struct File_info {
    typedef unsigned long long Size_type;
    Size_type filesize;
    size_t filename_size;
    File_info() : filesize(0), filename_size(0) {}
};

class Server{
//    friend std::string dealMessage(char data[],socket_ptr sock,std::shared_ptr<Server> server);

public:
    Server();
    //接收客户端的连接
    void connect();
    //判断客户端发来的消息的类型,并调用相应的处理函数
    std::string dealMessage(string sig, vector<string> str, socket_ptr sock);
    //接收客户端信息
//    boost::system::error_code &getMessage(socket_ptr sock,boost::system::error_code &ec);
    //分配客户端接收信息
    void receiveMessage(socket_ptr sock);
    void fileSender(std::string fileName, socket_ptr sock);

    //处理客户端请求的操作
//    void dealOperation();
    //处理客户端请求的数据
//    void dealData();

private:
    std::shared_ptr<FanProxy > _fanProxy;
    std::shared_ptr<SongListProxy> _songListProxy;
    std::shared_ptr<SongProxy> _songProxy;
    DatabaseController database;
};
//std::string dealMessage(char data[], socket_ptr sock, std::shared_ptr<Server> server);
#endif // FSINGSERVICE_H
