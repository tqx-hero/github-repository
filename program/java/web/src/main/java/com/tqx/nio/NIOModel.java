package com.tqx.nio;

import javax.xml.stream.events.StartDocument;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.StandardSocketOptions;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.nio.charset.StandardCharsets;
import java.util.Iterator;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/23 10:40
 */
public class NIOModel {

    private static ServerSocketChannel socketChannel = null;
    private static Selector selector = null;

    public static void main(String[] args) {

        try {
            socketChannel = ServerSocketChannel.open();
            socketChannel.bind(new InetSocketAddress(9090), 300);
//            socketChannel.setOption(StandardSocketOptions.SO_REUSEPORT, true);
            socketChannel.setOption(StandardSocketOptions.SO_REUSEADDR, true);
            socketChannel.configureBlocking(false);
            selector = Selector.open();
            socketChannel.register(selector, SelectionKey.OP_ACCEPT);
            for (; ; ) {
                int select = selector.select(15000);
                if (select == 0) continue;
                if (select == -1) break;
                Iterator<SelectionKey> iterator = selector.selectedKeys().iterator();
                while (iterator.hasNext()) {
                    SelectionKey key = iterator.next();
                    try {
                        if (!key.isValid())
                            continue;
                        if (key.isAcceptable()) {
                            connectHandler(key);
                            continue;
                        }
                        if (key.isReadable()) {
                            readHandler(key);
                        }
                    } catch (Exception e) {
                        System.out.println("客户端已退出");
                        shutDownChannel(key);
                    } finally {
                        iterator.remove();
                    }

                }
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        } finally {
            if (socketChannel != null) {
                try {
                    socketChannel.close();
                } catch (IOException e) {
                    throw new RuntimeException(e);
                } finally {
                    socketChannel = null;
                }
            }
            if (selector != null) {
                try {
                    removeKeys(selector);
                    selector.close();
                } catch (IOException e) {
                    throw new RuntimeException(e);
                } finally {
                    selector = null;
                }
            }
        }

    }

    static void removeKeys(Selector selector) {
        for (SelectionKey key : selector.selectedKeys()) {
            key.cancel();
            if (key.channel() instanceof SocketChannel
                    && !key.channel().isOpen()) {
                try {
                    key.channel().close();
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }


    static void shutDownChannel(SelectionKey key) {
        key.cancel();
        SelectableChannel channel = key.channel();
        if (channel != null) {
            try {
                channel.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            } finally {
                channel = null;
            }
        }
    }

    static void connectHandler(SelectionKey key) throws IOException {
        ServerSocketChannel channel = (ServerSocketChannel) key.channel();
        SocketChannel accept = channel.accept();
        accept.configureBlocking(false);
        accept.setOption(StandardSocketOptions.SO_RCVBUF, 1024 * 64);
        accept.setOption(StandardSocketOptions.SO_SNDBUF, 1024 * 64);
        accept.setOption(StandardSocketOptions.SO_KEEPALIVE, true);
        accept.setOption(StandardSocketOptions.TCP_NODELAY, true);
        //设置通道关闭时等待5秒发送最后的数据包，默认为直接关闭，会导致数据丢失
        //针对实时性要求高，互动频繁地如游戏、聊天等可以设置为0，直接关闭
        accept.setOption(StandardSocketOptions.SO_LINGER, 5);
        accept.register(key.selector(), SelectionKey.OP_READ);
        System.out.println("客户端:[" + accept.getRemoteAddress() + "] 已连接");
    }

    static void readHandler(SelectionKey key) throws IOException {
        SocketChannel channel = (SocketChannel) key.channel();
        ByteBuffer direct = ByteBuffer.allocate(1024);
        int read = channel.read(direct);
        if (read == -1) {
            channel.close();
            key.cancel();
            System.out.println("客户端:[" + channel.getRemoteAddress() + "]已断开");
        } else if (read > 0) {
            direct.flip();
            String string = StandardCharsets.UTF_8.decode(direct).toString();
            System.out.println("客户端发来消息：" + string);

            String reponse = "服务端收到消息：" + string;
            ByteBuffer buffer = ByteBuffer.wrap(reponse.getBytes(StandardCharsets.UTF_8));
            channel.write(buffer);
        }

    }

}
