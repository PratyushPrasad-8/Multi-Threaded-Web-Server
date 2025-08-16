# File Transfer System in C  

This project is a simple **client-server file transfer application** built in **C language**.  
It enables clients to upload and download files from a central server using **socket programming**.  

---

## 🚀 Features
- Upload files from client to server.  
- Download files from server to client.  
- Handles multiple client connections.  
- Reliable transfer using **TCP sockets**.  

---

## 🛠️ Tech Stack
- **Language**: C  
- **Concepts Used**: Socket Programming, TCP  

---

## 📂 Files
- `file_server.c` → Manages client connections, handles upload & download requests.  
- `file_client.c` → Connects to server, sends and receives files.  

---

## ⚙️ How to Run

### 1. Compile the Server and Client
```bash
gcc file_server.c -o file_server
gcc file_client.c -o file_client
```
### 2. Start the Server
```bash
./file_server
```
### 3. Run Client
```bash
./file_client
```
