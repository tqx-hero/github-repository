package com.tqx.socket;

import java.io.*;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.util.Objects;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/23 9:09
 */
public class ClientS {

    private static final int PORT = 9090;
    private static final String SERVER_IP = "127.0.0.1";
    private static final int TIME_OUT = 30000;

    private static Socket socket;
    private static PrintWriter writer;
    private static BufferedReader bufferedReader;
    private static Scanner scanner;
    private static ExecutorService executor;
    private static InputStreamReader reader;
    private static OutputStreamWriter w;

    private static boolean initConnection() {
        boolean flag = false;
        try {
            socket = new Socket();
            socket.connect(new InetSocketAddress(SERVER_IP, PORT), TIME_OUT);
            InputStream stream = socket.getInputStream();
            reader = new InputStreamReader(stream, StandardCharsets.UTF_8);
            bufferedReader = new BufferedReader(reader);
            OutputStream os = socket.getOutputStream();
            w = new OutputStreamWriter(os, StandardCharsets.UTF_8);
            writer = new PrintWriter(w, true);
            executor = Executors.newSingleThreadExecutor();
            scanner = new Scanner(System.in);
            flag = true;
        } catch (Exception e) {
            System.out.println("建立连接失败:" + e.getMessage());
            closeAllResources();
        }
        return flag;
    }


    private static void closeAllResources() {
        try {
            if (executor != null)
                executor.shutdown();
            if (socket != null)
                socket.close();
            if (writer != null)
                writer.close();
            if (bufferedReader != null)
                bufferedReader.close();
            if (scanner != null)
                scanner.close();
        } catch (Exception e) {
            System.out.println("关闭异常");
        } finally {
            executor = null;
            socket = null;
            writer = null;
            bufferedReader = null;
            scanner = null;
        }
    }

    public static void main(String[] args) {
        try {
            if (!initConnection()) {
                closeAllResources();
                return;
            }
            int count = 5;
            for (; count > 0; ) {
                System.out.print("请输入发送给服务器的消息（输入q退出）：");
                try {
                    Future<String> submit = executor.submit(() -> scanner.nextLine());
                    String res = submit.get(3, TimeUnit.MINUTES);
                    if ("q".equalsIgnoreCase(res)) {
                        writer.println(res);
                        break;
                    }
                    writer.println(res);
                    String s = bufferedReader.readLine();
                    System.out.println("服务端：" + s);
                } catch (SocketTimeoutException e) {
                    System.out.println("与服务器断开连接，正在重连....");
                    //重连服务器
                    count--;
                    if (!initConnection()) {
                        closeAllResources();
                        break;
                    }
                } catch (Exception e) {
                    System.out.println("与服务器连接出现异常:" + e.getMessage());
                    closeAllResources();
                    break;
                }
            }
        } catch (Exception e) {
            throw new RuntimeException(e);
        } finally {
            closeAllResources();
        }
    }

}
