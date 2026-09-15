package com.tqx.socket;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;
import java.util.Scanner;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/20 8:36
 */
public class NewSocket {

    public static void main(String[] args) {

        int port = 8888;
        ServerSocket socket = null;
        String BYE = "bye";
        try {
            socket = new ServerSocket(port);
            System.out.println("服务端已启动，端口：" + port + " ,等待客户端连接");
            while (true) {
                Socket client = socket.accept();
                System.out.println("客户已连接，地址：" + client.getInetAddress()
                        + ":" + client.getPort());

                InputStream is = client.getInputStream();
                BufferedReader reader = new BufferedReader(new InputStreamReader(is, StandardCharsets.UTF_8));
                OutputStream os = client.getOutputStream();
                PrintWriter writer = new PrintWriter(new OutputStreamWriter(os, StandardCharsets.UTF_8), true);
                String msg;
                Scanner scanner = new Scanner(System.in);
                while ((msg = reader.readLine()) != null) {
                    System.out.println("客户端消息：" + msg);
                    String res;
                    if ((res = scanner.nextLine()) != null) {
                        writer.println(res);
                    }
                    if (BYE.equals(msg)) {
                        break;
                    }
                }
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        } finally {
            if (socket != null) {
                try {
                    socket.close();
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }
}
