package com.tqx.socket;

import java.io.*;
import java.net.Socket;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/20 10:57
 */
public class Client {

    public static void main(String[] args) {
        String serverPort = "127.0.0.1";
        int port = 8888;
        Socket socket = null;
        String BYE = "bye";
        try {
            socket = new Socket(serverPort, port);

            System.out.println("已建立服务器连接：" + socket.getInetAddress() + ":" + socket.getPort());

            OutputStream os = socket.getOutputStream();
            PrintWriter writer = new PrintWriter(new OutputStreamWriter(os, StandardCharsets.UTF_8), true);
            InputStream is = socket.getInputStream();
            BufferedReader reader = new BufferedReader(new InputStreamReader(is, StandardCharsets.UTF_8));
            Scanner scanner = new Scanner(System.in);
            while (true) {
                String msg = scanner.nextLine();
                writer.println(msg);
                if (BYE.equals(msg)) {
                    break;
                }
                String ot = reader.readLine();
                System.out.println("服务端输出：" + ot);


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
