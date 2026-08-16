## AOP面向切面编程

###### 在不改变原有代码逻辑的基础上，在代码执行期间进行定制操作，用来增强代码功能的。

​	首先引入jar包：

```java
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-aop</artifactId>
</dependency>
```

定义AOP切面，并设置切点：

```java
@Aspect
@Component
public class LogAspect {


    @Around("execution(* com.spring.aop..*.*(..))")
    public void log(ProceedingJoinPoint jo) {

        long start = System.nanoTime();
        try {
            jo.proceed();
        } catch (Throwable e) {
            throw new RuntimeException(e);
        }

        long end = System.nanoTime();
        System.out.println("耗时：" + (end - start) / 1000.00 / 1000.00 + "s");
    }
}
```

##### 关于切点匹配表达式，execution()，从左到右依次为：（[修饰符] 返回值类型 包名.类名.方法名(参数列表)）[异常类型]

###### 1.访问修饰符包括public、protected、default和private，可省略，省略则代表所有修饰符类型

###### 2.返回值类型必须有，可以定义任何类型如String、Integer等，*代表匹配所有类型。

###### 3.包名，必选，aop..代表aop包下所有的子包，*代表所有单层包。

###### 4.类名，可选，*表示任意类型，可以前后缀匹配，如 *Service代表所有以service结束的所有类名,User * 代表所有以User开头的类名，区分大小写。

###### <!--*但注意：*-->

###### <!--*这里只匹配前缀后缀，不能中间匹配，如： *Ser不能匹配UserService这个类，只能匹配以Ser为末尾的类。*-->

###### 5.方法名，必选，*表示任意，与类名匹配相同。

###### 6.参数列表，必选。..代表所有，可指定参数类型如String，()代表无参。

###### 7.异常类型，可选，匹配抛出指定异常的方法，如 `throws Exception`。

##### 基本演示如下：

| 表达式                                                       | 匹配规则                                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `execution(public * com.example.service.UserService.save*(..))` | UserService 类中所有 public、以 save 开头、任意参数的方法    |
| `execution(* com.example.service..*.*(..))`                  | com.example.service 包及子包下所有类的所有方法               |
| `execution(* com.example.*.service.*.*(String))`             | com.example 任意子包下的 service 包中，所有单个 String 参数的方法 |
| `execution(void com.example..*.*())`                         | 任意子包下无参、返回值为 void 的所有方法                     |

##### 除了 `execution`，还有几个高频关键字，可单独使用或组合：

| 关键字        | 作用                           | 示例                                                         |
| ------------- | ------------------------------ | ------------------------------------------------------------ |
| `within`      | 匹配指定包 / 类下的所有方法    | `within(com.example.service..*)`（匹配该包及子包所有方法）类级别 |
| `@annotation` | 匹配标注了指定注解的方法       | `@annotation(com.example.annotation.Log)`（匹配标注 @Log 的方法） |
| `this`        | 匹配代理对象为指定类型的类     | `this(com.example.service.UserService)`                      |
| `target`      | 匹配目标对象为指定类型的类     | `target(com.example.service.UserService)`                    |
| `args`        | 匹配参数类型符合指定规则的方法 | `args(java.lang.String)`（匹配参数为 String 的方法）         |

#### 组合切点表达式（逻辑运算符）

可通过 `&&`（且）、`||`（或）、`!`（非）组合多个表达式，实现更精准的匹配：

```java
// 匹配 service 包下，标注了 @Log 且方法名以 save 开头的方法
@Pointcut("within(com.example.service..*) && @annotation(com.example.annotation.Log) && execution(* save*(..))")
public void logSavePointcut() {}

// 匹配 service 包下，除了 UserService 类之外的所有方法
@Pointcut("within(com.example.service..*) && !within(com.example.service.UserService)")
public void excludeUserServicePointcut() {}
```



#### *<u>基于针对方法注解形式的切点：</u>*

​	适用于对使用了注解的对象的方法进行操作，同时也可以根据AOP的功能非常方便的实现自定义注解。		

​	使用如下：

​	自定义一个Logs注解：

```java
@Target({ElementType.TYPE, ElementType.METHOD})
@Retention(RetentionPolicy.RUNTIME)
public @interface Logs {
    String value() default "";

    String desc() default "";
}
```

​	编写切面类，通过设置注解形式的切点捕获目标对象，并对其进行相关操作：

```java
@Component
@Aspect
public class AOPAspectj {
	//注解类型的切点，log必须与传参名称相同
    @Pointcut("@annotation(log)")
    public void pointCut(Logs log) {
    }

    @Around("pointCut(log)")
    public Object doAnn(ProceedingJoinPoint joinPoint, Logs log) {
        Object proceed;
        System.out.println("执行了注解");
        System.out.println("注解信息===" + log.value());
        try {
            proceed = joinPoint.proceed();
        } catch (Throwable e) {
            throw new RuntimeException(e);
        }
        return proceed;
    }
}
```

或者这样：

```java
@Component
@Aspect
public class AOPAspectj {

    //    @Pointcut("@annotation(log)")
    @Pointcut("@annotation(Logs)")
    public void pointCut() {
    }

    @Around("pointCut() && @annotation(log)")
    public Object doAnn(ProceedingJoinPoint joinPoint, Logs log) {
        Object proceed;
        System.out.println("执行了注解");
        System.out.println("注解信息===" + log.value());
        try {
            proceed = joinPoint.proceed();
        } catch (Throwable e) {
            throw new RuntimeException(e);
        }
        return proceed;
    }
}
```

不带参数的可以这样（但是通过反射方式获取注解信息会有性能损耗，该方法加载较慢）：

```java
@Component
@Aspect
public class AOPAspectj {

    @Pointcut("@annotation(Logs)")
    public void pointCut() {
    }

    @Around("pointCut()")
    public Object doAnn(ProceedingJoinPoint joinPoint) {
        Object proceed;
        System.out.println("执行了注解");
        Logs logs = joinPoint.getTarget().getClass().getAnnotation(Logs.class);
        MethodSignature signature = (MethodSignature) joinPoint.getSignature();
        Logs annotation = signature.getMethod().getAnnotation(Logs.class);
        System.out.println("类注解信息===" + logs.value());
        System.out.println("方法注解信息===" + annotation.value());
        try {
            proceed = joinPoint.proceed();
        } catch (Throwable e) {
            throw new RuntimeException(e);
        }
        return proceed;
    }
}
```

推荐使用软引用的SoftHashMap来对含有特定注解的类或方法进行缓存，省去在AOP执行期间反射获取值的时间，同时软引用还能保证不会对内存有太大影响。

示例如下：

##### a.引入预加载缓存的依赖：

```java
<!-- pom.xml 引入Reflections -->
<dependency>
    <groupId>org.reflections</groupId>
    <artifactId>reflections</artifactId>
    <version>0.10.2</version>
</dependency>
```

##### b.设置对应注解的映射对象，这里以Logs为例：

```java
public class LogsEntry {
    private String value;
    private String desc;

    public LogsEntry(String value, String desc) {
        this.value = value;
        this.desc = desc;
    }

    public String getDesc() {
        return desc;
    }

    public void setDesc(String desc) {
        this.desc = desc;
    }

    public String getValue() {
        return value;
    }

    public void setValue(String value) {
        this.value = value;
    }
}
```



##### c.编写缓存工具类：

```java
public class CacheLogs {

    private static final Map<Method, LogsEntry> METHOD_LOGS_ENTRY_MAP;
    private static final Map<Class, LogsEntry> CLASS_LOGS_ENTRY_MAP;

    static {
        CLASS_LOGS_ENTRY_MAP = new SoftHashMap<>();
        METHOD_LOGS_ENTRY_MAP = new SoftHashMap<>();
    }


    public static LogsEntry getMethodLogs(Method me) {
        if (METHOD_LOGS_ENTRY_MAP.containsKey(me))
            return METHOD_LOGS_ENTRY_MAP.get(me);
        Logs l = me.getAnnotation(Logs.class);
        if (l != null) {
            LogsEntry entry = new LogsEntry(l.value(), l.desc());
            METHOD_LOGS_ENTRY_MAP.put(me, entry);
            return entry;
        }
        return null;
    }

    public static LogsEntry getClassLogs(Class clazz) {
        if (CLASS_LOGS_ENTRY_MAP.containsKey(clazz))
            return CLASS_LOGS_ENTRY_MAP.get(clazz);
        Logs l = (Logs) clazz.getAnnotation(Logs.class);
        if (l != null) {
            LogsEntry entry = new LogsEntry(l.value(), l.desc());
            CLASS_LOGS_ENTRY_MAP.put(clazz, entry);
            return entry;
        }
        return null;
    }


    public static void clearClassCache() {
        CLASS_LOGS_ENTRY_MAP.clear();
    }

    public static void clearMethodCache() {
        METHOD_LOGS_ENTRY_MAP.clear();
    }

    public static void clearAllCache() {
        clearMethodCache();
        clearClassCache();
    }

}
```



##### 4.添加预热加载配置类：

```java
public class PreLoaderCache {

    //指定扫描的包，可根据项目自身情况使用配置文件映射
    private static final String SCAN_PACKAGES = "com.spring.aop.service";

    public static void preLoadCacheLogs() {
        Reflections reflections = new Reflections(SCAN_PACKAGES,
                new MethodAnnotationsScanner(),
                new TypeAnnotationsScanner());
        //缓存有注解的方法
        Set<Method> methodSet = reflections.getMethodsAnnotatedWith(Logs.class);
        if (Objects.nonNull(methodSet)) {
            methodSet.forEach(CacheLogs::getMethodLogs);
            System.out.println("注解方法已加入缓存，数量=" + methodSet.size());
        }

        //缓存有注解的类
        Set<Class<?>> classSet = reflections.getTypesAnnotatedWith(Logs.class);
        if (Objects.nonNull(classSet)) {
            classSet.forEach(CacheLogs::getClassLogs);
            System.out.println("注解类已加入缓存，数量=" + classSet.size());
        }
        System.out.println("缓存完毕");
    }

}
```

##### 5.实现预热接口，并注入spring：

```java
@Component
public class CommondLoaderLogsCache implements CommandLineRunner {
    @Override
    public void run(String... args) throws Exception {
        PreLoaderCache.preLoadCacheLogs();
    }
}
```



#### @EnableAspectJAutoProxy：

​      **在springboot中，这个注解会在容器启动时自动给添加上，依赖的@SpringBootApplication的自动装配功能。但是在spring项目中需要手动添加开启AOP代理的功能注解。在实际开发过程中仍然建议添加。**



### AOP中的专有术语：

#### 1.目标对象：

##### 	需要增强的对象就是目标对象。

#### 2.切面：

##### 	定义的带有@Aspectj的类就是切面类。

#### 3.通知（Advice）：

##### 	定义在目标对象的哪一部分进行增强，分为前置@Before、后置@After、环绕@Around等。

######   	@Before：在方法前调用的方法。

```java
@Aspect
@Component
public class LogAspect {

    @Before("pointCut()")
    public void me1(JoinPoint joinPoint) {
        System.out.println("前置通知");
        System.out.println("方法名=" + joinPoint.getSignature().getName());
        System.out.println("参数列表==" + Arrays.toString(joinPoint.getArgs()));
        System.out.println("目标对象===" + joinPoint.getTarget());
    }
}
```

###### 	  @After：方法调用完成后执行，在环绕通知里的finally{}部分中执行的就是后置通知。

```java
@Aspect
@Component
public class LogAspect {

    @After("pointCut()")
    public void after(JoinPoint jo) {
        System.out.println("后置通知");
        System.out.println("目标对象=" + jo.getTarget());
    }
}
```

######           @Around：在方法前后执行。

```java
@Aspect
@Component
public class LogAspect {

    @Around("pointCut()")
    public void log(ProceedingJoinPoint jo) {

        //获取方法名
//        String name = jo.getSignature().getName();
//        //获取参数列表
//        Object[] args = jo.getArgs();
//        System.out.println(name + "方法开始执行，参数列表：" + Arrays.toString(args));

        long start = System.nanoTime();
        try {
            //这里是方法的执行阶段，以这里为界，上半部分为前置通知，后半部分为返回通知
            jo.proceed();
        } catch (Throwable e) {
            //这里是抛出异常的通知
            throw new RuntimeException(e);
        }finally{
            //这里是后置通知
        }
        long end = System.nanoTime();
        System.out.println("耗时：" + (end - start) / 1000.00 / 1000.00 + "s");
    }
}
```

######  	 @AfterThrowing:方法抛出异常后执行。

```java
@Aspect
@Component
public class LogAspect {
    //可以通过设置throwing配置，e与方法中的参数名相同
    @AfterThrowing(value = "pointCut()",
    throwing = "e")
    public void exception(JoinPoint joinPoint,Exception e) {
        System.out.println("异常通知");
        System.out.println("异常信息：" + e.getMessage());
    }
}
```

###### 	  @AfterReturning:方法返回时执行，可以获得返回值，执行顺序在后置通知之前。

```java
@Aspect
@Component
public class LogAspect {

    @AfterReturning("pointCut()")
    public void returns(JoinPoint jo) throws Throwable {
        System.out.println("返回后通知");
//        System.out.println(jo.proceed());

    }
}
```

##### 返回值可通过@Around来获取：

```java
@Aspect
@Component
public class LogAspect {


    @Around("pointCut()")
    public Object log(ProceedingJoinPoint jo) {

        Object proceed;
        try {
            proceed = jo.proceed();
            System.out.println("返回值：" + proceed);
        } catch (Throwable e) {
            throw new RuntimeException(e);
        }
        return proceed;
    }
}
```

##### 或者通过在注解上添加returning属性方式：

```java
@Aspect
@Component
public class LogAspect {

    @AfterReturning(value = "pointCut()",
            returning = "result")
    public void returns(JoinPoint jo, Object result) throws Throwable {
        System.out.println("返回后通知");
        System.out.println("返回值：" + result);

    }
}
```



##### 执行顺序：

​	**正常情况：前置通知--> 目标方法----->返回通知--->后置通知（finally内）；**

​	**出现异常： 前置通知--->目标方法-----------> 返回通知 ---->异常通知 ------>后置通知**

​	**所以无论哪种情况，后置通知由于在finally代码块中，所以都会执行。**

#### 4.切点（Point Cut）：

​	从目标对象哪切入，在代码中以execution匹配表达式或者其他几种注解表示。

##### 	可以将切点声明一个方法，所有通知的value值设置成这个方法名，这样所有的通知均可通过该切点的匹配规则进行切入。

```java
@Aspect
@Component
public class LogAspect {
    //声明切点方法
    @Pointcut("execution(* com.spring.aop..*Service.*(..))")
    public void pointCut() {

    }

	//设置value值为切点的方法名
   @AfterThrowing(value = "pointCut()",
            throwing = "e")
    public void exception(JoinPoint joinPoint, Exception e) {
        System.out.println("异常通知");
        System.out.println("异常信息：" + e.getMessage());
    }
    
}
```

#### 5.连接点（Join Point）：

​	切点切入以后连接的部分，就是指对代码增强的那部分。

​	

#### 6.顾问（Advicor）：

​	将切点与通知封装成一个对象。

#### 7.织入（Weaving）：

​	增强代码的过程就是织入。