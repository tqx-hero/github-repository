package com.tqx.design.factory_strategy.demo;

import com.tqx.design.AnnotationScannerFactory;
import com.tqx.design.factory_strategy.SuperMarkets;
import com.tqx.design.factory_strategy.SuperMartStrategy;
import com.tqx.design.factory_strategy.WolmaStrategy;
import com.tqx.design.factory_strategy.ann.AutoInject;
import com.tqx.design.factory_strategy.ann.Inject;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/22 10:52
 */
@Inject
public class Wolma {

    //todo 暂未实现
    @AutoInject
    private SuperMartStrategy s;


    void getDiscount() {
        AnnotationScannerFactory ioc = AnnotationScannerFactory.getInstance();
        WolmaStrategy bean = (WolmaStrategy) ioc.getBean(SuperMarkets.WOLNA.get());
        bean.disCount();
    }

    public static void main(String[] args) {

    }

}
