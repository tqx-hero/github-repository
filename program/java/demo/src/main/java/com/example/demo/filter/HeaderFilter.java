package com.example.demo.filter;


import org.springframework.stereotype.Component;

import javax.servlet.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
@Component
public class HeaderFilter implements Filter {

    private String encoding;

    @Override
    public void init(FilterConfig filterConfig) throws ServletException {
        // 设置utf-8编码
        this.encoding = filterConfig.getInitParameter("requestEncoding");
        if (encoding == null || encoding.equalsIgnoreCase("UTF-8")) {
            encoding = "UTF-8";
        }
    }

    @Override
    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain)
            throws IOException, ServletException {
        HttpServletRequest httpRequest = (HttpServletRequest) request;
        HttpServletResponse httpResponse = (HttpServletResponse) response;
        httpRequest.setCharacterEncoding(encoding);
        httpResponse.setCharacterEncoding(encoding);
//        httpResponse.setContentType("text/html; charset=" + encoding);
        httpResponse.setContentType("application/json");
        // 将包装后的请求对象传递给过滤器链的下一个过滤器或目标资源
        chain.doFilter(request, response);
    }

    @Override
    public void destroy() {
        // 销毁代码（可选）
    }
}
