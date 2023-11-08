#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

int main() {
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cout << "Fehler beim Initialisieren von WSA" << std::endl;
        return 1;
    }

    // Server Socket erstellen
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cout << "Fehler beim Erstellen des Sockets" << std::endl;
        WSACleanup();
        return 1;
    }

    // Server Adresse konfigurieren
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);

    // Socket an Adresse binden
    iResult = bind(serverSocket, reinterpret_cast<SOCKADDR*>(&serverAddress), sizeof(serverAddress));
    if (iResult == SOCKET_ERROR) {
        std::cout << "Fehler beim Binden des Sockets" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Server in den Listening-Modus versetzen
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cout << "Fehler beim Wechsel in den Listening-Modus" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server läuft und wartet auf Verbindungen..." << std::endl;

    // Verbindung akzeptieren
    SOCKET clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "Fehler beim Akzeptieren der Verbindung" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Hier können Sie mit dem Client kommunizieren

    // Socket schließen
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
