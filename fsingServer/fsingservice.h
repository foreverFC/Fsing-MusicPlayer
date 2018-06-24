#ifndef FSINGSERVICE_H
#define FSINGSERVICE_H

#include <boost/asio.hpp>
#include <vector>
#include <string>

using std::vector;

class Server{
public:

    Server();

//    typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

    //接收客户端的连接
    void connect();
    //接受客户端传来的请求事务
//    friend void receiveMessage(socket_ptr sock);
    //判断客户端发来的消息的类型,并调用相应的处理函数
    std::string dealMessage(std::string sig, vector<std::string> str);
    //返回处理信息给客户端
//    void tansforResult(socket_ptr sock);

    //处理客户端请求的操作
//    void dealOperation();
    //处理客户端请求的数据
//    void dealData();
};
#endif // FSINGSERVICE_H