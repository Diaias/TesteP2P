#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstring>

int main()
{
    WSADATA wsa;

    int resultado = WSAStartup(MAKEWORD(2, 2), &wsa);

    if (resultado != 0)
    {
        std::cout << "Erro ao iniciar Winsock: " << resultado << "\n";
        return 1;
    }

    SOCKET meuSocket = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);

    if (meuSocket == INVALID_SOCKET)
    {
        std::cout << "Erro ao criar socket: "
                  << WSAGetLastError() << "\n";

        WSACleanup();
        return 1;
    }

    sockaddr_in6 servidor{};

    servidor.sin6_family = AF_INET6;
    servidor.sin6_port = htons(5000);

    inet_pton(
        AF_INET6,
        "::1",
        &servidor.sin6_addr
    );

    std::cout << "Tentando conectar...\n";

    int resultadoConnect = connect(
        meuSocket,
        (sockaddr*)&servidor,
        sizeof(servidor)
    );

    if (resultadoConnect == SOCKET_ERROR)
    {
        std::cout << "Erro ao conectar: "
                  << WSAGetLastError() << "\n";

        closesocket(meuSocket);
        WSACleanup();

        return 1;
    }

    std::cout << "CONECTOU NO SERVIDOR!\n";

    while (true)
    {
        std::string mensagem;

        std::cout << "Voce: ";
        std::getline(std::cin, mensagem);

        if (mensagem == "sair")
        {
            break;
        }

        int bytesEnviados = send(
            meuSocket,
            mensagem.c_str(),
            mensagem.size(),
            0
        );

        if (bytesEnviados == SOCKET_ERROR)
        {
            std::cout << "Erro ao enviar: "
                    << WSAGetLastError()
                    << "\n";
            break;
        }
    }

    closesocket(meuSocket);
    WSACleanup();

    return 0;
}