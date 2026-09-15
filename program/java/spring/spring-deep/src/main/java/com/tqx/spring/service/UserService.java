package com.tqx.spring.service;

import com.tqx.spring.dao.ServiceDao;
import lombok.AllArgsConstructor;
import org.springframework.stereotype.Service;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/12 10:37
 */
@Service
@AllArgsConstructor
public class UserService {

    private final ServiceDao serviceDao;

}
