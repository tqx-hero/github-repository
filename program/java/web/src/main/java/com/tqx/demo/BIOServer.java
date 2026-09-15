package com.tqx.demo;

import java.io.*;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.StandardSocketOptions;
import java.nio.charset.StandardCharsets;
import java.util.Objects;
import java.util.Scanner;
import java.util.concurrent.*;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/24 6:12
 */
public class BIOServer {
    private static ServerSocket server;
    private static final String ADDRESS = "127.0.0.1";
    private static final int PORT = 9090;
    //read()的超时时间，
    private static final int SO_TIMEOUT = 30000;
    //全连接队列的最大长度
    private static final int BACK_LOG = 200;
    //设置socket发送接收缓冲区大小，根据项目实际情况设置。
    // 实时互动场景设置小一些；
    // 需要吞吐量、大文件传输的适当调大，这里设置的是32k
    private static final int SO_SENFBUF = 1024 << 5;
    private static final int SO_REVBUF = 1024 << 5;

    private static Scanner scanner;
    private static ExecutorService executor = Executors.newSingleThreadExecutor();

    private static InputStream is;
    private static OutputStream os;
    private static OutputStreamWriter streamWriter;
    private static PrintWriter writer;
    private static InputStreamReader reader;
    private static BufferedReader br;

    //关闭socket中的相关资源
    static void closeResources() {
        try {
            if (Objects.nonNull(is))
                is.close();
            if (Objects.nonNull(os))
                os.close();
            if (Objects.nonNull(streamWriter))
                streamWriter.close();
            if (Objects.nonNull(writer))
                writer.close();
            if (Objects.nonNull(reader))
                reader.close();
            if (Objects.nonNull(br))
                br.close();
        } catch (IOException e) {
            System.out.println("资源关闭出现异常");
        } finally {
            is = null;
            os = null;
            streamWriter = null;
            writer = null;
            reader = null;
            br = null;
        }
    }

    public static void main(String[] args) {
        try {
            server = new ServerSocket();
            server.bind(new InetSocketAddress(ADDRESS, PORT), BACK_LOG);
            server.setReuseAddress(true);
            scanner = new Scanner(System.in);
            for (; ; ) {
                //阻塞等待连接
                Socket socket = server.accept();
                socket.setKeepAlive(true);
                socket.setTcpNoDelay(true);
                socket.setSoTimeout(SO_TIMEOUT);
                socket.setOption(StandardSocketOptions.SO_SNDBUF, SO_SENFBUF);
                socket.setOption(StandardSocketOptions.SO_RCVBUF, SO_REVBUF);

                is = socket.getInputStream();
                reader = new InputStreamReader(is, StandardCharsets.UTF_8);
                br = new BufferedReader(reader);
                String str;
                os = socket.getOutputStream();
                streamWriter = new OutputStreamWriter(os, StandardCharsets.UTF_8);
                writer = new PrintWriter(streamWriter, true);
                while (!(str = br.readLine()).isEmpty()) {
                    System.out.println("客户端发来消息:" + str);
                    try {
                        String response = executor.submit(() -> scanner.nextLine()).get(5, TimeUnit.MINUTES);
                        writer.println(response);
                    } catch (TimeoutException e) {
                        System.out.println("输入超时");
                        writer.println("输入超时");
                        closeResources();
                        break;
                    } catch (ExecutionException | InterruptedException e) {
                        System.out.println("线程池出现异常，正在关闭");
                        closeResources();
                        throw new RuntimeException(e);
                    }
                }
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        } finally {
            try {
                if (Objects.nonNull(server))
                    server.close();
                if (Objects.nonNull(scanner))
                    scanner.close();
                if (Objects.nonNull(executor))
                    executor.shutdown();
            } catch (IOException e) {
                server = null;
                scanner = null;
                executor = null;
            }
        }
    }
}
