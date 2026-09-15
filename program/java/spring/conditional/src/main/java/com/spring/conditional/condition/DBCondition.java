package com.spring.conditional.condition;

/**
 * @author Administrator
 * @version 1.0
 * @description: 这里根据类加载器是否能加载到数据库依赖中的某个核心类来判断使用的哪个数据库，实际情况会更加具体
 * @date 2026/3/9 11:54
 */
public class DBCondition {

    //判断是否为mysql数据库
    public static boolean isMysql() {
        ClassLoader loader = DBCondition.class.getClassLoader();
        try {
            return loader.loadClass("com.mysql.cj.jdbc.Driver") != null;
        } catch (ClassNotFoundException e) {
            return false;
        }
    }

    //判断是否为oracle数据库
    public static boolean isOracle() {
        ClassLoader loader = DBCondition.class.getClassLoader();
        try {
            return loader.loadClass("oracle.security.pki.OraclePKI") != null;
        } catch (ClassNotFoundException e) {
            return false;
        }
    }

}
