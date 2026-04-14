# Network Chat

A simple TCP client-server chat application written in C++ using POSIX sockets.

## Overview

This project implements a basic two-way terminal chat between a server and a client over a local TCP connection. The server waits for a client to connect, then both sides can exchange messages interactively until either party sends `exit`.

## Project Structure

```
Network_chat/
├── CMakeLists.txt
└── src/
    ├── server.cpp
    └── client.cpp
```

## Requirements

- Linux or macOS
- C++17 compatible compiler (GCC or Clang)
- CMake 3.10 or higher

## Build

```bash
cd Network_chat
mkdir build && cd build
cmake ..
make
```

This produces two executables inside the `build/` directory: `server` and `client`.

## Usage

Open two terminal windows.

**Terminal 1 — start the server:**
```bash
./server
```

**Terminal 2 — start the client:**
```bash
./client
```

The client connects to `127.0.0.1:8080`. Once connected, you can type messages in either terminal and they will appear on the other side.

To end the session, type `exit` in either terminal.

## How It Works

| Component | Role |
|-----------|------|
| `server.cpp` | Binds to port `8080`, listens for one incoming connection, then enters a read → reply loop |
| `client.cpp` | Connects to `127.0.0.1:8080`, then enters a send → receive loop |

Communication is synchronous and turn-based: the client sends first, the server replies, then the cycle repeats.

## Limitations

- Only one client can be connected at a time
- Messages are limited to 1024 bytes
- The chat is strictly turn-based (client sends → server replies)
- No encryption or authentication
