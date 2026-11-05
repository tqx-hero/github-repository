#### errno：

| #    | 宏              | 英文描述                                                | 中文说明                           |
| ---- | --------------- | ------------------------------------------------------- | ---------------------------------- |
| 1    | E2BIG           | Argument list too long                                  | 参数列表过长                       |
| 2    | EACCES          | Permission denied                                       | 权限不足，访问被拒                 |
| 3    | EADDRINUSE      | Address in use                                          | 地址已被占用                       |
| 4    | EADDRNOTAVAIL   | Address not available                                   | 地址不可用                         |
| 5    | EAFNOSUPPORT    | Address family not supported                            | 地址族不支持                       |
| 6    | EAGAIN          | Resource unavailable, try again（可能等同 EWOULDBLOCK） | 资源暂不可用，请重试               |
| 7    | EALREADY        | Connection already in progress                          | 连接已在进行中                     |
| 8    | EBADF           | Bad file descriptor                                     | 无效文件描述符                     |
| 9    | EBADMSG         | Bad message                                             | 报文 / 消息损坏                    |
| 10   | EBUSY           | Device or resource busy                                 | 设备或资源忙                       |
| 11   | ECANCELED       | Operation canceled                                      | 操作已取消                         |
| 12   | ECHILD          | No child processes                                      | 无子进程                           |
| 13   | ECONNABORTED    | Connection aborted                                      | 连接被中止                         |
| 14   | ECONNREFUSED    | Connection refused                                      | 连接被拒绝                         |
| 15   | ECONNRESET      | Connection reset                                        | 连接被重置                         |
| 16   | EDEADLK         | Resource deadlock would occur                           | 将发生资源死锁                     |
| 17   | EDESTADDRREQ    | Destination address required                            | 需要目的地址                       |
| 18   | EDOM            | Mathematics argument out of domain of function          | 数学参数超出函数定义域             |
| 19   | EDQUOT          | Reserved                                                | 保留（配额相关，POSIX 标为保留项） |
| 20   | EEXIST          | File exists                                             | 文件已存在                         |
| 21   | EFAULT          | Bad address                                             | 地址无效                           |
| 22   | EFBIG           | File too large                                          | 文件过大                           |
| 23   | EHOSTUNREACH    | Host is unreachable                                     | 主机不可达                         |
| 24   | EIDRM           | Identifier removed                                      | 标识符已被删除                     |
| 25   | EILSEQ          | Illegal byte sequence                                   | 非法字节序列                       |
| 26   | EINPROGRESS     | Operation in progress                                   | 操作正在进行                       |
| 27   | EINTR           | Interrupted function                                    | 函数调用被中断                     |
| 28   | EINVAL          | Invalid argument                                        | 参数无效                           |
| 29   | EIO             | I/O error                                               | 输入输出错误                       |
| 30   | EISCONN         | Socket is connected                                     | 套接字已连接                       |
| 31   | EISDIR          | Is a directory                                          | 对象是目录                         |
| 32   | ELOOP           | Too many levels of symbolic links                       | 符号链接层数过多                   |
| 33   | EMFILE          | File descriptor value too large                         | 进程文件描述符数超限               |
| 34   | EMLINK          | Too many links                                          | 硬链接数过多                       |
| 35   | EMSGSIZE        | Message too large                                       | 消息过大                           |
| 36   | EMULTIHOP       | Reserved                                                | 保留（多跳访问，POSIX 标为保留项） |
| 37   | ENAMETOOLONG    | Filename too long                                       | 文件名过长                         |
| 38   | ENETDOWN        | Network is down                                         | 网络已关闭                         |
| 39   | ENETRESET       | Connection aborted by network                           | 连接被网络中止                     |
| 40   | ENETUNREACH     | Network unreachable                                     | 网络不可达                         |
| 41   | ENFILE          | Too many files open in system                           | 系统打开文件总数超限               |
| 42   | ENOBUFS         | No buffer space available                               | 无可用缓冲区空间                   |
| 43   | ENODATA         | No message is available on the STREAM head read queue   | STREAM 读队列无消息                |
| 44   | ENODEV          | No such device                                          | 无此设备                           |
| 45   | ENOENT          | No such file or directory                               | 无此文件或目录                     |
| 46   | ENOEXEC         | Executable file format error                            | 可执行文件格式错误                 |
| 47   | ENOLCK          | No locks available                                      | 无可用锁                           |
| 48   | ENOLINK         | Reserved                                                | 保留（链接失效，POSIX 标为保留项） |
| 49   | ENOMEM          | Not enough space                                        | 内存空间不足                       |
| 50   | ENOMSG          | No message of the desired type                          | 无所需类型的消息                   |
| 51   | ENOPROTOOPT     | Protocol not available                                  | 协议选项不可用                     |
| 52   | ENOSPC          | No space left on device                                 | 设备空间已满                       |
| 53   | ENOSR           | No STREAM resources                                     | 无 STREAM 资源                     |
| 54   | ENOSTR          | Not a STREAM                                            | 非 STREAM 对象                     |
| 55   | ENOSYS          | Function not supported                                  | 功能未实现 / 不支持                |
| 56   | ENOTCONN        | The socket is not connected                             | 套接字未连接                       |
| 57   | ENOTDIR         | Not a directory or a symbolic link to a directory       | 不是目录（也不是指向目录的链接）   |
| 58   | ENOTEMPTY       | Directory not empty                                     | 目录非空                           |
| 59   | ENOTRECOVERABLE | State not recoverable                                   | 状态不可恢复                       |
| 60   | ENOTSOCK        | Not a socket                                            | 不是套接字                         |
| 61   | ENOTSUP         | Not supported（可能等同 EOPNOTSUPP）                    | 不支持该操作                       |
| 62   | ENOTTY          | Inappropriate I/O control operation                     | 不适当的 I/O 控制操作              |
| 63   | ENXIO           | No such device or address                               | 无此设备或地址                     |
| 64   | EOPNOTSUPP      | Operation not supported on socket（可能等同 ENOTSUP）   | 套接字上不支持该操作               |
| 65   | EOVERFLOW       | Value too large to be stored in data type               | 值超出数据类型可存储范围           |
| 66   | EOWNERDEAD      | Previous owner died                                     | 前一个所有者已终止                 |
| 67   | EPERM           | Operation not permitted                                 | 操作不被允许                       |
| 68   | EPIPE           | Broken pipe                                             | 管道破裂                           |
| 69   | EPROTO          | Protocol error                                          | 协议错误                           |
| 70   | EPROTONOSUPPORT | Protocol not supported                                  | 协议不支持                         |
| 71   | EPROTOTYPE      | Protocol wrong type for socket                          | 套接字协议类型错误                 |
| 72   | ERANGE          | Result too large                                        | 结果超出范围                       |
| 73   | EROFS           | Read-only file system                                   | 只读文件系统                       |
| 74   | ESPIPE          | Invalid seek                                            | 非法定位（如对管道 seek）          |
| 75   | ESRCH           | No such process                                         | 无此进程                           |
| 76   | ESTALE          | Reserved                                                | 保留（陈旧句柄，POSIX 标为保留项） |
| 77   | ETIME           | Stream ioctl() timeout                                  | STREAM ioctl 超时                  |
| 78   | ETIMEDOUT       | Connection timed out                                    | 连接超时                           |
| 79   | ETXTBSY         | Text file busy                                          | 文本文件忙（正在执行）             |
| 80   | EWOULDBLOCK     | Operation would block（可能等同 EAGAIN）                | 操作将阻塞                         |
| 81   | EXDEV           | Cross-device link                                       | 跨设备链接                         |