#include <winsock2.h>
#include <iostream>

int main()
{
    WSADATA wsa;

    int resultado = WSAStartup(MAKEWORD(2,2), &wsa);
    
    if (resultado != 0)
    {
        std::cout << "Erro ao iniciar Winsock " << resultado << "\n";
        return 1;
    }
    
    
    SOCKET meuSocket = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);


    if (meuSocket == INVALID_SOCKET)
    {
        std::cout << "Erro ao criar socket: "
                << WSAGetLastError()
                << "\n";

        WSACleanup();
        return 1;
    }

    std::cout << "Criou saporra\n";

    closesocket(meuSocket);
    WSACleanup();

    return 0;
}

