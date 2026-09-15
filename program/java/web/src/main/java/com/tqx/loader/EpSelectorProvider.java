//package com.tqx.loader;
//
//
//import java.io.IOException;
//import java.nio.channels.spi.AbstractSelector;
//
///**
// * @author Administrator
// * @version 1.0
// * @description: TODO
// * @date 2026/3/25 11:47
// */
//public class EpSelectorProvider extends SelectorProviderImpl{
//    public static void main(String[] args) {
//        String cn = System.getProperty("java.nio.channels.spi.SelectorProvider");
//        System.out.println(cn);
//        String cn1 = System.setProperty("java.nio.channels.spi.SelectorProvider","com.tqx.loader.EpSelectorProvider");
//        cn = System.getProperty("java.nio.channels.spi.SelectorProvider");
//        System.out.println(cn);
//    }
//
//    @Override
//    public AbstractSelector openSelector() throws IOException {
//        return new EpSelectorImpl(this);
//    }
////    public class WEPollSelectorProvider extends SelectorProviderImpl {
////        public AbstractSelector openSelector() throws IOException {
////            return new WEPollSelectorImpl(this);
////        }
////    }
//
////    private static final SelectorProviderImpl INSTANCE;
////    static {
////        PrivilegedAction<SelectorProviderImpl> pa = WEPollSelectorProvider::new;
////        INSTANCE = AccessController.doPrivileged(pa);
////    }
////
////    /**
////     * Prevent instantiation.
////     */
////    private DefaultSelectorProvider() { }
////
////    /**
////     * Returns the default SelectorProvider implementation.
////     */
////    public static SelectorProviderImpl get() {
////        return INSTANCE;
////    }
//
//}
