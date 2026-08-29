1. HTTP请求头(GET)：

   ###### 报文格式：(\r\n为每行结束标志，空格作为字段结束标志):

   ```http
   //请求类型(GET/POST等) 要请求的资源 协议类型/版本\r\n
   GET /a.txt HTTP/1.1\r\n
   //请求的目的IP:port\r\n
   Host: 192.168.1.178:8080\r\n
   ...
   ```

   

   ![image-20260829110748907](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260829110748907.png)

2. 应答报文格式：

   ###### 报文格式(以\r\n作为一行结束标志,空格作为字段结束标志)：

   ```http
   //版本 状态码 信息\r\n
   HTTP/1.1 200 OK\r\n
   //日期、服务器信息、连接类型(keep-Alive或者Close)、Keep-Alive时间设置等可以省略
   //文本长度(数据部分长度)\r\n
   Content-Length: 数据长度\r\n
   //修改时间等可省略
   //数据类型(文本/JSON/表单/多媒体文件等)\r\n
   Content-Type: text/html\r\n
   //空行，不能省略，代表响应头的结束，数据部分的开始
   \r\n
   data.....
   ```

   

   ![image-20260829114511065](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260829114511065.png)

3. 相应状态码：![image-20260829114933396](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260829114933396.png)

   

4. 文本类型Content-Type(MIME类型):

   text/*类型(文本):

   主要是字符文本，可指定字符集如：

   text/plain;charset=utf-8

   ```http
   text/plain	// 纯文本
   text/html //静态界面
   text/css  //css样式表
   text/javascript(application/javascript)	//js脚本
   text/xml	//xml文本
   text/csv	//csv表格，逗号分隔数据
   ```

   demo:

   ```http
   Content-Type: text/html;charset=utf-8
   ```

   

5. application/*(内容可读的非文本字符串)格式：

   ```http
   application/json	//JSON数据，接口API最常用,非text类型
   application/x-www-form-urlencoded	//普通POST表单默认格式，键值对URL编码
   application/xml		//xml数据
   application/javascript		//js脚本推荐格式(代替旧格式text/javascript)
   multipart/form-data			//文件上传表单(POST表单)，多部份混合，二进制+文本(如：文本内容+音视频照片等)
   application/octet-stream 	//二进制字节流，未知类型文件
   ```

   demo:

   ```http
   Content-Type: application/json
   ```

   

6. image/*(图片二进制非文本)格式：

   ```http
   image/jpeg
   image/png
   image/gif
   image/svg+xml
   ```

   

7. 