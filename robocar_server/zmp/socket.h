#ifndef MR_SOCKET_H_
#define MR_SOCKET_H_

#include <map>
#include <string>
#include <memory>
#include <tr1/memory>
#include <netinet/in.h>
//#include "globals.h"
#include "ring_buffer.h"



// currentry sender implemeted only.
class UDPSocket {
public:
	UDPSocket();
	~UDPSocket();
	bool Setup(const char *hostname, int port);
	int Send(const void *buf, size_t count);
private:
	sockaddr_in addr_;
	int sock_;
};

class SocketClientUDP {
public:
	SocketClientUDP();
	virtual ~SocketClientUDP();
	bool Setup(const char *hostname, int port);
	bool Send(const void *buf, size_t count);
private:
	UDPSocket sock_;
};


// --- T C P S o c k e t ------------------------------------------------------
/**
 *
 */
class TCPSocket {
  public:
    typedef int SocketType;

    TCPSocket();
    ~TCPSocket();

    int Connect(const char* hostname, const char* port);
    int Bind(const char* hostname, const char* port);
    int Listen(int backlog);
    /**
     * Accept a connection form a client and return
     * a new TCPSocket instance that represents the new connection.
     * @return  A new TCPSocket instance that represents the new connection.
     */
    std::auto_ptr<TCPSocket> Accept();
    int Shutdown();

    int Send(const void* buf, size_t count);
    int Receive(void* out_buf, size_t count);
    void SetNonBlocking();

    int descriptor() const { return descriptor_; }
    const char* hostname() const { return hostname_.c_str(); }
    const char* port() const { return port_.c_str(); }
    bool connecting() const { return connecting_; }

  private:
    explicit TCPSocket(int sock);
    int descriptor_;
    std::string hostname_;
    std::string port_;
    bool connecting_;

    DISALLOW_COPY_AND_ASSIGN(TCPSocket);
};

// --- S o c k e t E v e n t H a n d l e r I n t e r f a c e ------------------
/**
 *
 */
class SocketEventHandlerInterface {
  public:
    virtual ~SocketEventHandlerInterface() { }
    /**
     * Invoked when a SocketServer instance read a new data from client socket.
     * This method is called in a receiving thread of SocketServer.
     * @param[in] receive_buf  The receive buffer of SocketServer.
     */
    virtual void ReceiveProc(RingBuffer* receive_buf) = 0;
    /**
     * Invoked
     * This method is called in a receiving thread of SocketServer.
     */
    virtual void InitStatus() = 0;
    /**
     * Invoked when socket connection status changed.
     * This method is called in a receiving thread of SocketServer.
     */
    virtual void OnConnectionOpen(std::string info) = 0;
    virtual void OnConnectionAccept(std::string info) = 0;
    virtual void OnConnectionClose(std::string info) = 0;
    virtual void OnConnectionDisconnect(std::string info) = 0;

};

// --- S o c k e t S e r v e r ------------------------------------------------
///
/// Asynchronous socket server using epoll and non-blocking I/O.
///
/// Usage:
///
/// HALMessageDispatcher hal;
/// SocketServer server(&hal, NULL, 9123, 10, 1024);
/// server.Start();
///
///
class SocketServer {
  public:
    static const int kReceiveBufferSize = 10 * 1024;

    /// @param[in] host Host IP address like "127.0.0.1".
    ///            If NULL is supplied, INADDR_ANY is used internally.
    ///
    SocketServer(SocketEventHandlerInterface* handler,
                 const char* port,
                 unsigned int max_cilent,
                 unsigned int recv_buf_size);
    ///
    ~SocketServer();

    ///
    ///
    ///
    bool Start();
    ///
    ///
    ///
    void WaitForShutdown();
    ///
    ///
    ///
    bool Send(const unsigned char* msg, unsigned int len, int id);
    ///
    void ShutdownAllClients();
    ///
    bool is_active() const { return is_active_; }

    bool is_connect() const { return (client_socks_.size() > 0); }

    bool GetClientName(char *name);
  private:
    ///
    void ReceiveThread();
    ///
    static void* ReceiveThreadEntry(void* arg);
    ///
    bool HandleAccept();
    ///
    bool HandleRead(TCPSocket* sock);
    ///
    bool HandleClose(TCPSocket* sock);
    ///
    void ShutdownClient(int sock_fd);

    TCPSocket server_sock_;
    std::map< int, std::tr1::shared_ptr<TCPSocket> > client_socks_;
    RingBuffer recv_buf_;
    SocketEventHandlerInterface* handler_;
    unsigned int recv_buf_size_;
    pthread_t recv_thread_;
    std::string port_;
    /// Number of connection
    unsigned int max_clients_;

    bool is_active_;
    bool enable_;

    int epoll_fd_;

    DISALLOW_COPY_AND_ASSIGN(SocketServer);
};


// --- S o c k e t R e a d e r -----------------------------------------------
///
struct LineSeparator {
    typedef enum {
        CRLF,
        CR,
        LF,
    } Type;
};

class SocketReader {
  public:
    typedef std::vector<byte_t> Buffer;

    static const int kNumberToRead = 1 * 1024;
    static const int kReceiveBufferSize = 10 * 1024;

    explicit SocketReader(TCPSocket* sock_ptr);
    SocketReader(TCPSocket* sock_ptr, LineSeparator::Type line_sep);

    std::auto_ptr< std::vector<byte_t> > Read(unsigned int nread);
    std::auto_ptr< std::vector<byte_t> > ReadLine();

    LineSeparator::Type line_sep() const { return line_sep_; }
    void set_line_sep(LineSeparator::Type value) { line_sep_ = value; }
  private:
    TCPSocket* sock_ptr_;
    RingBuffer recv_buf_;
    LineSeparator::Type line_sep_;

    DISALLOW_COPY_AND_ASSIGN(SocketReader);
};

//}} // namespace miuro::internal

#endif/*MR_SOCKET_H_*/

