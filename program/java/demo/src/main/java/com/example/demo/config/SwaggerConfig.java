package com.example.demo.config;

import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.boot.autoconfigure.condition.ConditionalOnExpression;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import springfox.documentation.builders.ApiInfoBuilder;
import springfox.documentation.builders.PathSelectors;
import springfox.documentation.builders.RequestHandlerSelectors;
import springfox.documentation.service.ApiInfo;
import springfox.documentation.service.Contact;
import springfox.documentation.spi.DocumentationType;
import springfox.documentation.spring.web.plugins.Docket;
import springfox.documentation.swagger2.annotations.EnableSwagger2;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/2/17 9:36
 */
@Configuration(proxyBeanMethods = false)
@EnableSwagger2
@ConditionalOnExpression("${button.building.swagger.enabled:true}")
public class SwaggerConfig {
    @Bean
    public Docket createRestApi() {
        return new Docket(DocumentationType.SWAGGER_2)
                .apiInfo(apiInfo())
                .select()
                .apis(RequestHandlerSelectors.basePackage("com.example"))
                //basePage就是具体要扫描的包，有swagger注解的方法就生成到文档里面去
                .apis(RequestHandlerSelectors.withClassAnnotation(Api.class))
                .apis(RequestHandlerSelectors.withMethodAnnotation(ApiOperation.class))
                .paths(PathSelectors.any())
                .build();
    }
    private ApiInfo apiInfo() {
        return new ApiInfoBuilder()
                .title("公司管理api")
                .description("公司管理接口文档说明")
                .contact(new Contact("灵图软件",
                        "http://www.lingtu.com",
                        "demo@lingtu.com"))
                .version("1.0")
                .build();
    }
//    @Bean
//    UiConfiguration uiConfig() {
//        return new UiConfiguration(null, "list", "alpha", "schema",
//                UiConfiguration.Constants.DEFAULT_SUBMIT_METHODS, false, true, 60000L);
//    }
}
