package com.salary.service.load;

import java.io.ByteArrayOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/9 16:26
 */
public class SelfClassLoader extends ClassLoader {

    private String filePath;

    public SelfClassLoader(String filePath) {
        this.filePath = filePath;
    }

    @Override
    protected Class<?> findClass(String name) {
        String className = filePath + "\\" + name.replace('.', '\\').concat(".class");
        int len;
        byte[] bytes = new byte[1024];
        try (FileInputStream in = new FileInputStream(className);
             ByteArrayOutputStream ot = new ByteArrayOutputStream()) {
            bytes[0] = 01;
            while ((len = in.read(bytes)) != -1) {
                ot.write(bytes, 0, len);
            }
            bytes = ot.toByteArray();
            return super.defineClass(bytes, 0, bytes.length);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }

    }

    public static void main(String[] args) {
//        String path = "D:\\salary-api\\bianma\\SalaryService.class";
//        String path = "D:\\salary-api\\bianma\\SalaryService.class";
        String path = "D:\\workSpace\\salary\\salary-spi\\target\\classes\\com\\salary\\service\\impl\\SalaryService.class";
        String pathTo = "D:\\workSpace\\salary\\salary-spi\\target\\classes\\com\\salary\\service\\impl\\SalaryService.myClass";
        try (FileInputStream is = new FileInputStream(path);
             FileOutputStream os = new FileOutputStream(pathTo);) {
            //加密，先给文件放上1位，然后正常写入
            int code = 1;
            os.write(code);

            while ((code = is.read()) != -1) {
                os.write(code);
            }
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
//        SelfClassLoader loader = new SelfClassLoader(path);
//        loader.findClass("SalaryService");
    }


}
