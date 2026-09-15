package com.salary.test;


import com.salary.loader.JarClassLoader;
import com.salary.service.ISalaryService;

import java.lang.reflect.InvocationTargetException;
import java.util.Iterator;
import java.util.Objects;
import java.util.ServiceLoader;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/9 13:16
 */
public class MySalary {

    public static void main(String[] args) throws InterruptedException, ClassNotFoundException, NoSuchMethodException, InvocationTargetException, InstantiationException, IllegalAccessException {

        Double salary = 10000.00;
        Double money;
        String ip = "D:\\workSpace\\salary-spi\\target\\salary-spi-1.0-SNAPSHOT.jar";
//        String ip = "D:\\salary-api\\lib\\salary-spi-1.0-SNAPSHOT.jar";
//        String ip2 = "D:\\salary-api\\lib2\\salary-spi-1.0-SNAPSHOT.jar";
        //读取jar包中的class文件
        //通过修改class后缀为.myClass进行更安全的读取
        while (true) {
//            JarClassLoader loader2 = new JarClassLoader(ip2);
//            Double money2 = getSalary(salary, loader2);
//            System.out.println("当前工资=====" + money2);

            JarClassLoader loader = new JarClassLoader(ip);

            ServiceLoader<ISalaryService> services = (ServiceLoader<ISalaryService>) LoadServiceLoaderList.getList(loader, ISalaryService.class);

            services.forEach(salaryService -> {
                System.out.println("工资=============" + salaryService.mySalary(salary));
            });
            //            JarInputMyClassClassLoader loader = new JarInputMyClassClassLoader(ip);
//            money = getSalary(salary, loader);
//            System.out.println("我的工资是" + money);
            Thread.sleep(5000);
        }
    }


    //通过类加载器加载class文件并加载到JVM内存中
    public static Double getSalary(Double salary, ClassLoader classLoader) {
        try {
            Class<?> aClass = classLoader.loadClass("com.salary.service.SalaryService");
            if (Objects.nonNull(aClass)) {
                return (Double) aClass.getMethod("mySalary", Double.class).invoke(aClass.getConstructor().newInstance(), salary);
            }
            return -1.0;
        } catch (Exception e) {
            System.out.println("正在加载中......");
            e.printStackTrace();
            return -1.0;
        }
    }
}
