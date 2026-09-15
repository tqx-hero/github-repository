package com.tqx.socket;

import java.io.*;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.nio.channels.SelectableChannel;
import java.nio.channels.ServerSocketChannel;
import java.nio.charset.StandardCharsets;
import java.util.Objects;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/23 8:52
 */
public class Server {

    //设置服务器建立的全连接队列容量，最大容量不能超过linux默认最大上限128（这个最大值可通过设置net.core.somaxconn参数调整）,如果不设置，默认也
    //是这个参数值
    private static final int BACK_LOG = 20;
    private static final int PORT = 9090;
    //设置socket的读取超时时间，超过时长read()则会抛出异常
    private static final int SO_TIME_OUT = 50000;

    public static void main(String[] args) {
        ServerSocket socket = null;
        ExecutorService executor = Executors.newSingleThreadExecutor();
        try {
            socket = new ServerSocket();
            //设置端口复用，用于在服务关闭后短时间内重启能立即复用端口的状况
            //linux在tcp连接断开后，端口号会保留一段时间（1-4m），进入time_wait状态，
            // 是为了保证这边最后一个Ack包能传达给对方，避免连接残留
            //同时防止旧链接的数据包被新链接接收。
            //服务端这边必须显式设置，否则服务down掉之后重启出现端口被占用的尴尬场面
            socket.setReuseAddress(true);
            socket.bind(new InetSocketAddress(PORT), BACK_LOG);
            Scanner scanner = new Scanner(System.in);
            for (; ; ) {
                BufferedReader reader = null;
                PrintWriter writer = null;
                Socket client = null;
                try {
                    client = socket.accept();
                    //设置socket的读取等待最大时间，超时后再次读取会抛出异常
                    client.setSoTimeout(SO_TIME_OUT);
                    //开启心跳检测，超过心跳检测次数无响应的直接中断连接，
                    // 释放资源
                    client.setKeepAlive(true);
                    //是否开启数据实时发送
                    //true则会直接发送数据，不论数据量大小
                    //false则会把数据包进行打包，当超过一定大小后才会发送，适合需要大文件传输，不适合实时聊天的场景
                    client.setTcpNoDelay(true);
////                    SelectableChannel channel = client.getChannel().configureBlocking(false);
//                    ServerSocketChannel channel = socket.getChannel();
//                    channel.configureBlocking(false);
//                    channel.
                    System.out.println("客户端：" + client.getInetAddress().getHostAddress() + "已连接，端口号：" + client.getPort());
                    InputStream is = client.getInputStream();
                    reader = new BufferedReader(new InputStreamReader(is, StandardCharsets.UTF_8));
                    OutputStream os = client.getOutputStream();
                    writer = new PrintWriter(new OutputStreamWriter(os, StandardCharsets.UTF_8), true);
                    String msg = reader.readLine();

                    for (; msg != null; ) {
                        if (msg.isEmpty()) continue;
                        System.out.println(msg);
                        //线程池设置超时时间，到点关闭
                        String re = executor.submit(() ->
                                scanner.nextLine()
                        ).get(3, TimeUnit.MINUTES);
                        if ("q".equalsIgnoreCase(re)) {
                            writer.println("q");
                            break;
                        }
                        writer.println(re);
                    }

                } catch (SocketTimeoutException e) {
                    System.out.println("连接超时：" + e.getMessage());
                    writer.println("你已超过超过30秒没有发送消息");
                } catch (Exception e) {
                    System.out.println("系统异常");
                } finally {
                    if (Objects.nonNull(writer)) {
                        writer.close();
                    }
                    if (client != null) {
                        client.close();
                    }
                    if (Objects.nonNull(reader)) {
                        try {
                            reader.close();
                        } catch (IOException e) {
                            throw new RuntimeException(e);
                        } finally {
                            reader = null;
                        }
                    }
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            executor.shutdown();
            if (socket != null && !socket.isClosed()) {
                try {
                    socket.close();
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
                socket = null;
            }
        }
    }

}
