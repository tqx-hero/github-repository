package com.example.demo.entity;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;
import java.util.List;
import java.util.Set;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/2/17 12:33
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class BasicInfoVO implements Serializable {
    private static final long serialVersionUID = 1783749382970083324L;

    private BasicInfo basicInfo;

    private Set<Location> locations;

}
