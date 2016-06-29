#include <boost/asio.hpp>
#include <iostream>
#include <string>
using namespace std;
namespace asio = boost::asio;
namespace ip = asio::ip;

int client();
int server();

int main()
{
    char c;
    cout << "�N���C�A���g�H�T�[�o�[�Hc/s\n>";
    cin >> c;
    if (c == 'c')
    {
        client();
    }
    else if (c == 's')
    {
        server();
    }
}

int client()
try
{
    asio::io_service io_service;

    //TCP�\�P�b�g���쐬����
    ip::tcp::socket sock(io_service);

    //�z�X�g�����擾
    cout << "�T�[�o�[��\n>";
    string server_name;
    cin >> server_name;
    cout << "�|�[�g�ԍ�\n>";
    u_short port = 0;
    cin >> port;
    sock.connect(ip::tcp::endpoint(ip::address::from_string(server_name), port));

    //���b�Z�[�W�𑗎�M
    string buffer;
    while (true)
    {
        cout << "���M\n>";
        cin >> buffer;
        asio::write(sock, asio::buffer(buffer));
        if (buffer == "end")
        {
            break;
        }
        cout << "�T�[�o�[����Ԏ���҂��Ă��܂�\n";

        asio::streambuf receive_buffer;
        boost::system::error_code error;
        asio::read(sock, receive_buffer, asio::transfer_at_least(1), error);
        if (error && error != asio::error::eof)
        {
            std::cout << "receive failed: " << error.message() << std::endl;
        }
        else if (asio::buffer_cast<const char*>(receive_buffer.data()) == string("end"))
        {
            cout << "�T�[�o�[���ڑ���؂�܂���\n";
            break;
        }

        cout << "��M:" << &receive_buffer << endl;
    }

    return 0;
}
catch (exception& e)
{
    cout << e.what();
    return 1;
}

int server()
try
{
    asio::io_service io_service;

    //TCP�\�P�b�g���쐬����
    ip::tcp::socket sock(io_service);

    //IPv4�̃\�P�b�g�A�h���X����ݒ肷��
    cout << "�|�[�g�ԍ�\n>";
    u_short port = 0;
    cin >> port;
    ip::tcp::acceptor acceptor(io_service, ip::tcp::endpoint(ip::tcp::v4(), port));

    //�N���C�A���g����̐ڑ����󂯓����
    acceptor.accept(sock);

    //���b�Z�[�W�𑗎�M
    string buffer;
    while (true)
    {
        cout << "�N���C�A���g����̎�M��҂��Ă��܂�\n>";
        asio::streambuf receive_buffer;
        boost::system::error_code error;
        asio::read(sock, receive_buffer, asio::transfer_at_least(1), error);
        if (error && error != asio::error::eof)
        {
            std::cout << "receive failed: " << error.message() << std::endl;
        }
        else if (asio::buffer_cast<const char*>(receive_buffer.data()) == string("end"))
        {
            cout << "�N���C�A���g���ڑ���؂�܂���\n";
            break;
        }

        cout << "��M:" << &receive_buffer << endl;

        cout << "���M\n>";
        cin >> buffer;
        asio::write(sock, asio::buffer(buffer));
        if (buffer == "end")
        {
            break;
        }
    }
    return 0;
}
catch (exception& e)
{
    cout << e.what();
    return 1;
}