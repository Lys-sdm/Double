#pragma once
#include <bits/stdc++.h>
#include "logger.h"

#include <winsock2.h>
#include <ws2tcpip.h>
// #pragma comment(lib, "ws2_32.lib")   // MinGW 无效，编译命令加 -lws2_32

bool UdpSend(const std::string& ip, int port, const std::string& message) {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        LOG("[UdpSend] WSAStartup 失败");
        return false;
    }

    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        LOG("[UdpSend] socket 创建失败, err=" << WSAGetLastError());
        WSACleanup();
        return false;
    }

    sockaddr_in target{};
    target.sin_family      = AF_INET;
    target.sin_port        = htons((u_short)port);
    target.sin_addr.s_addr = inet_addr(ip.c_str());

    int ret = sendto(sock, message.c_str(), (int)message.size(), 0,
                     (sockaddr*)&target, sizeof(target));

    closesocket(sock);
    WSACleanup();

    if (ret == SOCKET_ERROR) {
        LOG("[UdpSend] 发送失败, err=" << WSAGetLastError());
        return false;
    }
    LOG("[UdpSend] 已向 " << ip << ":" << port << " 发送 " << ret << " 字节: " << message);
    return true;
}

std::string UdpReceive(int port, std::string& outMsg, int* outPort = nullptr) {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        LOG("[UdpReceive] WSAStartup 失败");
        return "";
    }

    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        LOG("[UdpReceive] socket 创建失败, err=" << WSAGetLastError());
        WSACleanup();
        return "";
    }

    sockaddr_in local{};
    local.sin_family      = AF_INET;
    local.sin_port        = htons((u_short)port);
    local.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (sockaddr*)&local, sizeof(local)) == SOCKET_ERROR) {
        LOG("[UdpReceive] bind 失败, 端口 " << port
            << " 可能被占用, err=" << WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return "";
    }

    LOG("[UdpReceive] 等待接收（端口 " << port << "）...");

    char buf[4096];
    sockaddr_in from{};
    int fromLen = sizeof(from);

    int len = recvfrom(sock, buf, sizeof(buf) - 1, 0,
                       (sockaddr*)&from, &fromLen);

    std::string fromIp;
    if (len > 0) {
        buf[len] = '\0';
        fromIp = inet_ntoa(from.sin_addr);
        outMsg.assign(buf, len);
        if (outPort) *outPort = ntohs(from.sin_port);

        LOG("[UdpReceive] 收到来自 " << fromIp << ":" << ntohs(from.sin_port)
            << " 的消息: " << outMsg);
    } else {
        LOG("[UdpReceive] recvfrom 错误, err=" << WSAGetLastError());
    }

    closesocket(sock);
    WSACleanup();
    return fromIp;
}
