package com.salary.service;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/9 13:25
 */
public class SalaryService implements ISalaryService {
    public Double mySalary(Double salary) {
        return salary * 1.2;
    }
}
