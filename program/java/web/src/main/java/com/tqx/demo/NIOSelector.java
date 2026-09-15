package com.tqx.demo;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.StandardSocketOptions;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.nio.charset.StandardCharsets;
import java.util.Iterator;
import java.util.Objects;
import java.util.Scanner;
import java.util.concurrent.*;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/24 6:12
 */
public class NIOSelector {

    private static final String ADDRESS = "127.0.0.1";
    private static final int PORT = 9090;
    private static final int BACK_LOG = 200;
    private static final int SELECT_TIME_OUT = 15 * 1000;
    private static final int RECVBUF = 1024 << 5;
    private static final int SENDBUF = 1024 << 5;
    //设置连接中断的超时时间，单位s
    private static final int LINGERTIME = 3;
    private static final boolean NO_DELY = true;


    private static ServerSocketChannel socketChannel;
    private static SocketChannel channel;
    private static Selector selector;
    private static Scanner scanner;
    private static ExecutorService executorService;

    private static final String SYS_LINUX = "linux";

    private static void closeResources() {
        try {
            if (Objects.nonNull(socketChannel))
                socketChannel.close();
            if (Objects.nonNull(selector))
                selector.close();
            if (Objects.nonNull(channel))
                channel.close();
            if (Objects.nonNull(scanner))
                scanner.close();
            if (Objects.nonNull(executorService))
                executorService.shutdown();
        } catch (Exception e) {
            socketChannel = null;
            selector = null;
            channel = null;
            scanner = null;
            executorService.shutdown();
        }
    }

    public static boolean configSystem(String sysName) {
        return System.getProperty("os.name").toLowerCase().contains(sysName.toLowerCase());
    }

    private static void initResource() {
        try {
            //设置serverSocketChannel
            socketChannel = ServerSocketChannel.open();
            socketChannel.bind(new InetSocketAddress(ADDRESS, PORT), BACK_LOG);
            socketChannel.configureBlocking(false);
            socketChannel.setOption(StandardSocketOptions.SO_REUSEADDR, true);
            //设置selector监听器,与服务socket绑定
            selector = Selector.open();
            if (configSystem(SYS_LINUX)) {
                System.out.println("linux操作系统设置ET模式");
                socketChannel.register(selector, SelectionKey.OP_ACCEPT | 0x1000);
            }
            executorService = Executors.newSingleThreadExecutor();
            scanner = new Scanner(System.in);
        } catch (Exception e) {
            System.out.println("资源初始化失败");
            closeResources();
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {
        try {
            initResource();
            int reConnectNum = 5;
            for (; ; ) {

                int clientCount = selector.select(SELECT_TIME_OUT);
                System.out.println("多路复用...............");
                if (clientCount == 0)
                    continue;
                if (clientCount < 0) {
                    System.out.println("selector出现故障，正在重启");
                    closeResources();
                    initResource();
                    continue;
                }
                Iterator<SelectionKey> keyIterator = selector.selectedKeys().iterator();
                for (; keyIterator.hasNext(); ) {
                    SelectionKey key = keyIterator.next();
                    keyIterator.remove();
                    if (!key.isValid()) {
                        try {
                            key.channel().close();
                        } catch (IOException e) {
                            throw new RuntimeException(e);
                        }
                        continue;
                    }
                    //连接资源，注册读取监听
                    if (key.isAcceptable()) {
//                        System.out.println("keys=="+key.interestOps(SelectionKey.OP_READ));
                        try {
                            channel = initClientSocket(key);
                        } catch (Exception e) {
                            System.out.println("客户端注册失败");
                            if (Objects.nonNull(channel)) {
                                try {
                                    channel.close();
                                } catch (IOException ex) {
                                    throw new RuntimeException(ex);
                                }
                            }
                            key.cancel();
                            continue;
                        }
                    }
                    //操作读取资源
                    if (key.isReadable()) {
                        System.out.println("readkeys==" + key.interestOps());
                        try {
                            channel = (SocketChannel) key.channel();
                            ByteBuffer buffer = ByteBuffer.allocate(1024);
                            int readCount = channel.read(buffer);
                            if (readCount == 0)
                                continue;
                            //读取异常，需要重新加载
                            if (readCount < 0) {
                                if (reConnectNum == 0) {
                                    System.out.println("重试次数已到，正在关闭该连接");
                                    key.cancel();
                                    channel.close();
                                    continue;
                                }
                                reConnectNum--;
                                closeResources();
                                initResource();
                                continue;
                            }
                            buffer.flip();
                            String msg = StandardCharsets.UTF_8.decode(buffer).toString();
                            System.out.println("客户端信息：" + msg);
                            executorService.submit(()
                                            -> {
                                        String response = scanner.nextLine();
                                        if (Objects.nonNull(response)) {
                                            try {
                                                channel.write(ByteBuffer.wrap(msg.getBytes(StandardCharsets.UTF_8)));
                                            } catch (IOException e) {
                                                System.out.println("消息读取异常");
                                                scanner.close();
                                                try {
                                                    channel.close();
                                                } catch (IOException ex) {
                                                    channel = null;
                                                    throw new RuntimeException(ex);
                                                }
                                                throw new RuntimeException(e);
                                            }
                                        }
                                    }
                            ).get(30, TimeUnit.SECONDS);
                        } catch (IOException e) {
                            System.out.println("读取客户端数据异常。");
                            try {
                                channel.close();
                            } catch (IOException ex) {
                                throw new RuntimeException(ex);
                            }
                            key.cancel();
                        }

                    }

                }

            }

        } catch (ExecutionException e) {
            System.out.println("线程池出现异常");
            throw new RuntimeException(e);
        } catch (InterruptedException e) {
            System.out.println("线程池被中断");
            throw new RuntimeException(e);
        } catch (TimeoutException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        } finally {
            closeResources();
        }

    }


//    static void readHandler(SelectionKey key,int reConnectNum) {
//        try {
//            channel = (SocketChannel) key.channel();
//            ByteBuffer buffer = ByteBuffer.allocate(1024);
//            int readCount = channel.read(buffer);
//            //读取异常，需要重新加载
//            if (readCount < 0) {
//                if (reConnectNum == 0) {
//                    System.out.println("重试次数已到，正在关闭该连接");
//                    key.cancel();
//                    channel.close();
//                }else{
//                    reConnectNum--;
//                    closeResources();
//                    initResource();
//                }
//            } else if (readCount > 0) {
//                buffer.flip();
//                String msg = StandardCharsets.UTF_8.decode(buffer).toString();
//                System.out.println("客户端信息：" + msg);
//                msg = executorService.submit(() -> scanner.nextLine()).get(30, TimeUnit.SECONDS);
//                if (Objects.nonNull(msg)) {
//                    channel.write(ByteBuffer.wrap(msg.getBytes(StandardCharsets.UTF_8)));
//                }
//            }
//        } catch (IOException e) {
//            System.out.println("读取客户端数据异常。");
//            try {
//                channel.close();
//            } catch (IOException ex) {
//                throw new RuntimeException(ex);
//            }
//            key.cancel();
//        }
//
//    }


    private static SocketChannel initClientSocket(SelectionKey key) {
        socketChannel = (ServerSocketChannel) key.channel();
        try {
//            channel = socketChannel.accept();
            //设置ET模式
            for (; Objects.nonNull(channel = socketChannel.accept()); ) {
                channel.configureBlocking(false);
                SelectionKey clientKey = channel.register(selector, SelectionKey.OP_READ);
                if (configSystem(SYS_LINUX))
                    clientKey.interestOps(clientKey.interestOps() | 0x1000);
                channel.setOption(StandardSocketOptions.SO_RCVBUF, RECVBUF);
                channel.setOption(StandardSocketOptions.SO_SNDBUF, SENDBUF);
                channel.setOption(StandardSocketOptions.SO_KEEPALIVE, true);
                channel.setOption(StandardSocketOptions.SO_LINGER, LINGERTIME);
                channel.setOption(StandardSocketOptions.TCP_NODELAY, NO_DELY);
            }
        } catch (ClosedChannelException e) {
            System.out.println("channel异常关闭");
            try {
                channel.close();
                key.cancel();
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        } catch (IOException e) {
            System.out.println("IO异常");
            try {
                channel.close();
                key.cancel();
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        }
        return channel;
    }

}
