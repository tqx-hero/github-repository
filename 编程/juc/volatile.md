# volatile

#### 1、CPU的三级缓存：

##### 	CPU在去内存中存读数据时不与内存直接交互，中间会有三级缓存，从浅到深一次为L1、L2、L3。

#### 2、java内存：

##### 	JAVA的多线程模型与CPU的缓存模型类似，同样不会与内存直接交互，是基于缓存建立起来的，每个线程都有一个独立的工作内存，线程隔离，当内存中存在数据，JVM会将数据存储到自身线程的内存中，典型的示例如下：

```java
public class Test {
	//静态变量是存储到内存中，在没有volatile情况下flag在第一个子线程的内存中一直为false，循环不会结束
    private static  boolean flag = false;

    public static void main(String[] args) throws InterruptedException {
        new Thread(() -> {
            System.out.println("线程1启动");
            while (!flag) {

            }
            System.out.println("线程1结束");
        }).start();

        Thread.sleep(5000);

        new Thread(() -> {
            System.out.println("线程2启动");
            flag = true;
            System.out.println("线程2结束");
        }).start();
    }
}
```

#### 3、内存的8大原子操作：

##### 	read：从内存读取数据

##### 	load：把数据加载到线程的工作内存

##### 	use：线程使用数据

##### 	assign：线程修改工作内存中的数据

##### 	store：线程将修改值推送到主内存

##### 	write：主内存写入新数据

##### 	lock：添加内存屏障，使其前后的代码不能越过屏障执行，禁止了指令重排

##### 	unlock：

#### 4、缓存一致性协议(MESI)

 	没有该协议：

​		1、线程A从主内存read数据；

​		2、线程A加载load数据到工作内存；

​		3、线程A拿取工作内存数据并use；

​		4、线程B同样操作use数据（工作内存与A的隔离）；

​		5、线程B修改工作内存数据（assign）；

​		6、线程B结束后store，将数据推送到内存；

​		7、内存写入修改的数据write。

##### 	有了该协议后：

​		1-5同样操作；

​		6、线程B修改内存数据后，立即将新数据store，内存write；

​		7、在推送新数据过程中，经过总线，触发总线嗅探机制；

​		8、触发嗅探机制后，会将其余线程（这里是线程A）中这个数据失效处理（硬件支持的）；

​		9、线程A在use数据时发现数据已失效，重新read内存，load数据，此时数据已是线程B修改过的数据。

#### 5、volatile的缓存可见性原理：

​	底层实现是通过汇编指令的lock，它会锁定这块内存区域的缓存（缓存行锁定）并将新数据写回到主内存。

步骤如下：

##### 	1、会将当前处理器的缓存行的数据立刻写如内存；

##### 	2、该写入操作会将CPU缓存中使用这个内存地址的数据无效；

##### 	3、提供内存屏障，使lock前后指令无法重排序。

#### 6、指令重排：

​	规则：

​		在同一个线程里，如果指令打乱顺序不会影响这个线程中数据的最终结果，CPU为了提高性能会对指令进行重新排序，打乱原有的代码逻辑，但是会遵循一定语义：as-if-serial和happens-before。

##### 	as-inf-serial语义：不管怎么重排序（编译器和CPU为了提高并行效率），单线程的程序执行结果不能改变。编译器、runtime和CPU都必须遵守该语义；

##### 	happens-before：在指令重排后不能改变程序的原有语义（单线程），比如单线程内针对同一对象的锁，若当前持有锁，程序写的是先unlock在执行lock的话，如果对其重排成先lock后unlock，那结果就由持有一把锁变成了可重入锁，即持有两把锁，语义已经变了，这种情况就不能进行重排。



#### 7、双重检测锁单例(DCL--Double Check Lock)的半初始化问题

```java
public class LazySingleton {
    //没有添加volatile，可能在synchronized代码块中进行指令重排序
    private static LazySingleton instance;

    public static int num = 1000;
    
    private LazySingleton() {
    }

    public static LazySingleton getInstance() {
        if (instance == null) {
            synchronized (LazySingleton.class) {
                if (instance == null) {
                    instance = new LazySingleton();
                }
            }
        }
        return instance;
    }
}
```

##### 以上单例在高并发情况下可能会导致拿到的对象是未赋值的,即有可能num的值为0；

##### 在锁内进行的操作如果按顺序执行的话应该是这样的：

###### 	1、判断instance是否为空，如果为空，则进行new对象，下面开始new对象操作；

###### 	2、查看类有没有被加载器加载，没有则先加载类；

###### 	3、元空间中存在类的结构信息后，开始为对象分配内存地址；

###### 	4、分配完地址后，给对象的静态变量赋初始值，以上情况就是int num = 0；instance = null；

###### 	5、调用init()，开始赋程序中的值，即设置num的值1000，执行构造方法进行实例化，即new LazySingleton()；

###### 	6、把对象实例的地址赋值给instance。

###### 	7、后续就是解锁返回操作。

##### 	在这里因为没用volatile修饰静态变量，5和6步骤可能会进行指令重排，重排也遵守单线程中的as-if-serial和happens-before语义，所以这种重排的可能性存在。

#### 假设6与5步骤对调，那么重排后的情况是这样的：

##### 	1、线程A给instance赋值实例地址后，下一步就要对其进行赋值以及初始化。

##### 	2、此时线程B刚进入方法，此时进行instance进行判断，由于线程A已经分配好了地址值给instance，所以instance不为空，此时线程B会直接拿到这个未初始化完成的instance。



#### 8、内存屏障：

##### 	java规范规定了四种屏障类型，包括：

###### 		A、LoadLoad ：  Load1; LoadLoad;Load2;  	Load2的读操作一定要在Load1的读操作完成之后。

###### 		B、StoreLoad： Store1; StoreLoad; Load2;  	Load2的读操作一定要在Store1写入内存完成并刷新成功后再进行

###### 		C、StoreStore： Store1;StoreStore;Store2;	Store2的写操作一定要在Store1写入内存并刷新成功后再进行，即Store2在写之前拿取的是Store1写入后的新值。

###### 		D、LoadStore：Load1;LoadStore;Store2;	Store2的写操作一定要在Load1的读取操作完成后执行。



##### volatile关键字在jdk底层的实现逻辑就是，在对使用volatile修饰的变量进行操作时，会对这个变量加一个lock，这个不是java语言中的锁，是内存屏障，意思是将对这个变量操作所在行的前后隔离开来，以达到上面java规范的要求，以此来禁止指令重排。