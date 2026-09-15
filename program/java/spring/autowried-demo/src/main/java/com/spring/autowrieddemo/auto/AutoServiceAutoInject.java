package com.spring.autowrieddemo.auto;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/8 17:31
 */
@Service
public class AutoServiceAutoInject {

    private AutoService autoService;

    private ProductService productService;

    public AutoServiceAutoInject(AutoService autoService) {
        this.autoService = autoService;
    }


    public ProductService getProductService() {
        return productService;
    }

    @Autowired
    public void setProductService(ProductService productService) {
        this.productService = productService;
    }

    public void say() {
        autoService.say();
    }


    public void productSay() {
        productService.say();
    }
}
