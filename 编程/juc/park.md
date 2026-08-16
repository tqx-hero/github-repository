### LockSuport.park

与wait效果相同，都是将所在线程进行阻塞，但相较于wait使用更灵活轻便。

1、wait需要使用synchroinzed代码块中，即需要先加锁在wait，因为wait在线程进入等待队列之前先释放锁，所以必须在加锁情况下使用，该操作是JVM层面上的，属于用户态层面，即线程放入monitor的等待队列wait Set中。

​	park则没有该限制，随时使用，随时让线程进入内核态的阻塞状态，此时由操作系统控制，该线程不会再占用时间片，JVM仅记录其相关的许可以及状态，后续等待unpark唤醒。

2、wait需要notify唤醒，但是notify是随机性的唤醒，不能指定，notifyAll是唤醒全部。

​	park需要unpark来给于许可后线程才会被唤醒。在unpark时可以指定唤醒哪个线程，用起来更方面。

3、wait的唤醒必须在使用wait之后才能调用notify来唤醒，有先后顺序。

​	park没有该顺序要求。即可以先unpark给于线程许可，在park，此时park的线程已经有了许可就不会再次挂起，直接继续进行。



##### 虽然park使用很方便灵活，但是基于操作系统，会有偶尔park中途的线程突然唤醒的情况，这与操作系统有关系，没法避免，所以在使用park的时候，如果想避免这种情况可以添加判断条件，不满足条件的继续park：

​	

```java
while (你的判断条件) {
    LockSupport.park();
}
```



