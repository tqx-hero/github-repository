package com.tqx.thread.atomic;

import java.util.concurrent.atomic.AtomicStampedReference;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/18 11:17
 */
public class PrivateAtomicStampReference<T> extends AtomicStampedReference<T> {

    //规定版本号最大值为整型的一半
    private static final int MAX_STAMP = Integer.MAX_VALUE >> 1;
    //最大版本号值
    private int maxStamp;


    /**
     * Creates a new {@code AtomicStampedReference} with the given
     * initial values.
     *
     * @param initialRef   the initial reference
     * @param initialStamp the initial stamp
     */
    private PrivateAtomicStampReference(T initialRef, int initialStamp) {
        super(initialRef, initialStamp);
    }

    public PrivateAtomicStampReference(T initialRef, int initialStamp, int maxStamp) {
        super(initialRef, initialStamp);
        this.maxStamp = Math.min(maxStamp, MAX_STAMP);
    }

    @Override
    public boolean weakCompareAndSet(T expectedReference, T newReference, int expectedStamp, int newStamp) {
        return super.weakCompareAndSet(expectedReference, newReference, expectedStamp, newStamp > maxStamp ? 0 : newStamp);
    }

    @Override
    public boolean compareAndSet(T expectedReference, T newReference, int expectedStamp, int newStamp) {
        return super.compareAndSet(expectedReference, newReference, expectedStamp, newStamp > maxStamp ? 0 : newStamp);
    }
}

class Test {
    public static void main(String[] args) {
        AtomicStampedReference<Integer> reference = new PrivateAtomicStampReference<Integer>(0, 99, 100);
        reference.compareAndSet(0, 1, 99, 100);
        reference.compareAndSet(1, 2, 100, 101);
        System.out.println(reference.getStamp());
    }
}
