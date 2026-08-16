# **一、Bean的生命周期**

**1、配置@Configuration、@Compont、@Bean等方式声明将该Bean注入；**

**2、生成spring容器（new AppConfigurationContext()）。**

**3、容器生成Bean的对象（new clazz()）；**

**4、DI**

***5、初始化，调用初始化方法；***

**6、初始化完成后的Bean放入容器，Map<beanName,Bean对象>。**

**7、 使用Bean，spring通过key的方式去Map中拿取Bean对象。**

***8、容器销毁，Bean也随着销毁**，同时也会调用销毁的回调方法。*****



# **二、生命周期的回调函数**

## 1、初始化回调实现形式：

### **①、基于实现接口InitializingBean，回调afterPropertiesSet()**

```java
public class BeanService implements InitializingBean {
    //1、初始化完成后的回调函数
    @Override
    public void afterPropertiesSet() throws Exception {
        System.out.println("Bean初始化成功-接口形式");
    }
}
```

### ②、基于注解@PostConstruct：

```java
//2、基于注解形式回调
@PostConstruct
public void initSuccess() {
    System.out.println("注解形式回调加载成功");
}
```

### ③、基于@Bean的initMethod属性

```java
    @Bean(initMethod = "initMethod")
    public BeanService beanService() {
        return new BeanService();
    }
```

#### 	同时在BeanService中指定该方法

```java
    //3、基于@Bean的initMethod变量指定加载方法
    public void initMethod() {
        System.out.println("Bean的加载方法回调成功");
    }

```

三者的顺序是：注解-->接口--->initMethod()。



## 2、销毁回调函数：

### ①、基于接口,实现DisposableBean接口

```java
public class BeanService implements InitializingBean, DisposableBean {
    @Override
    public void destroy() throws Exception {
        System.out.println("Bean销毁成功，接口形式");
    }
}
```

### ②、基于注解

```java
@PreDestroy
public void destoryBean() {
    System.out.println("Bean销毁，基于注解");
}
```

### ③、基于destoryMethod

```java
public void destory() {
    System.out.println("Bean销毁成功，destoryMethod属性");
}
```

```java
@Bean(initMethod = "initMethod",destroyMethod = "destory")
public BeanService beanService() {
    return new BeanService();
}
```

三者调用顺序同样为：注解--->接口--->destoryMethod方法。

> [!WARNING]
>
> ###### 在Springboot中销毁时会自动调用close方法，但是spring项目中需要手动去关闭容器。





