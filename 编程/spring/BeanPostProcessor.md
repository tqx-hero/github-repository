### BeanPostProcessor：

#### 	Bean处理器：

##### 	特殊bean，统一在bean的生命周期初始化前后阶段拦截，所以初始化要比其他的bean更早，类型是接口，有两个方法postProcessAfterInitialization和postProcessBeforeInitialization，分别在bean初始化前和初始化后调用，AOP就是在after方法内进行的。

##### 	该接口可扩展，通过实现该接口，重写这两个方法即可对bean的初始化前后进行增强。

> [!CAUTION]
>
> #### 但是一定要注意：
>
> #### 1、因为是由spring去管理bean，该接口的实现类必须注册成一个bean。
>
> #### 2、由于处理器需要对其他bean做初始化前后管理，初始化时机较早，所以注入spring时必须放到其他配置类外，单独配置，否则会失效。
>
> ```java
> @Configuration
> public class SpringConfig {
> 
> 
>     @Bean(initMethod = "init")
>     public ServiceDao serviceDao() {
>         return new ServiceDao();
>     }
> 	//此种方式会失效，因为此时的初始化顺序是配置类早于处理器
>     @Bean
>     public ServicePostProcessor servicePostProcessor() {
>         return new ServicePostProcessor();
>     }
> 
> }
> ```
>
> #### 3、同时也不能让其他bean比如service等去实现，同样不符合其初始化时机
>
> ```java
> //此种方式也不会生效
> @Service
> public class UserService implements BeanPostProcessor {
>     @Autowired
>     private ServiceDao serviceDao;
> 
>     public UserService() {
>         System.out.println("service实例化....");
>     }
> 
>     @Override
>     public Object postProcessAfterInitialization(Object bean, String beanName) throws BeansException {
> 
>         System.out.println("after");
> 
>         return null;
>     }
> 
>     @Override
>     public Object postProcessBeforeInitialization(Object bean, String beanName) throws BeansException {
>         System.out.println("before");
>         return null;
>     }
> }
> ```

#### 正确的注入方式是单独以注解的方式将实现类注入到spring容器。

```java
@Component
public class ServicePostProcessor implements BeanPostProcessor {

    public ServicePostProcessor() {
        System.out.println("processor初始化");
    }

    @Override
    public Object postProcessAfterInitialization(Object bean, String beanName) throws BeansException {
        if (beanName.equals("serviceDao") || beanName.equals("servicePostProcessor") || beanName.equals("springConfig")) {
            System.out.println(beanName + " after");
        }
        return BeanPostProcessor.super.postProcessAfterInitialization(bean, beanName);
    }

    @Override
    public Object postProcessBeforeInitialization(Object bean, String beanName) throws BeansException {
        if (beanName.equals("serviceDao") || beanName.equals("servicePostProcessor") || beanName.equals("springConfig")) {
            System.out.println(beanName + " before");
        }
        return BeanPostProcessor.super.postProcessBeforeInitialization(bean, beanName);
    }
}
```