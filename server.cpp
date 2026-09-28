#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

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

    sockaddr_in6 endereco{};

    endereco.sin6_family = AF_INET6;
    endereco.sin6_port = htons(5000);
    endereco.sin6_addr = in6addr_any;

    int resultadobind = bind(
        meuSocket,
        (sockaddr*)&endereco,
        sizeof(endereco)
    );

    if (resultadobind == SOCKET_ERROR){
        std::cout << "Erro no bind: "
                << WSAGetLastError()
                << "\n";

        closesocket(meuSocket);
        WSACleanup();

        return 1;
    }

    std::cout << "Bind realizado na porta 5000!\n";

    int resultadoListen = listen(meuSocket, SOMAXCONN);

    if (resultadoListen == SOCKET_ERROR)
    {
        std::cout << "Erro no listen: "
                << WSAGetLastError()
                << "\n";

        closesocket(meuSocket);
        WSACleanup();

        return 1;
    }

    std::cout << "Esperando conexoes na porta 5000...\n";


    SOCKET socketCliente = accept(
        meuSocket,
        nullptr,
        nullptr
    );

    if (socketCliente == INVALID_SOCKET)
    {
        std::cout << "Erro no accept: "
                << WSAGetLastError()
                << "\n";

        closesocket(meuSocket);
        WSACleanup();

        return 1;
    }

    std::cout << "ALGUEM CONECTOU!\n";

    while (true)
    {
        char buffer[1024];

        int bytesRecebidos = recv(
            socketCliente,
            buffer,
            sizeof(buffer) - 1,
            0
        );

        if (bytesRecebidos > 0)
        {
            buffer[bytesRecebidos] = '\0';

            std::cout << "Cliente: "
                    << buffer
                    << "\n";
        }
        else if (bytesRecebidos == 0)
        {
            std::cout << "Cliente desconectou.\n";
            break;
        }
        else
        {
            std::cout << "Erro no recv: "
                    << WSAGetLastError()
                    << "\n";
            break;
        }
    }

    closesocket(socketCliente);
    closesocket(meuSocket);
    WSACleanup();
    return 0;
}

