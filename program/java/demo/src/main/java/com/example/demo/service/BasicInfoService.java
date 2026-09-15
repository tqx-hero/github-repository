package com.example.demo.service;

import com.example.demo.entity.BasicInfo;
import com.example.demo.entity.BasicInfoVO;
import com.example.demo.entity.Result;

import java.util.List;

public interface BasicInfoService {
    Result<String> add(BasicInfo basicInfo);

    Result<String> update(BasicInfo basicInfo);

    Result<List<BasicInfoVO>> listAll(List<Integer> ids);

    Result<String> delete(List<Integer> ids) throws Exception;

    Result<String> addBatch(List<BasicInfo> basicInfoList);
}
