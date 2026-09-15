package com.tqx.design.factory_strategy.demo;

import com.tqx.design.AnnotationScannerFactory;
import com.tqx.design.factory_strategy.SuperMarkets;
import com.tqx.design.factory_strategy.WolmaStrategy;

class WolmaTest {

    void getDiscount() {
        AnnotationScannerFactory ioc = AnnotationScannerFactory.getInstance();
        WolmaStrategy bean =(WolmaStrategy) ioc.getBean(SuperMarkets.WOLNA.get());
        bean.disCount();
    }

}