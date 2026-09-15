package com.example.demo.mapper;

import com.example.demo.entity.BasicInfo;

import java.util.List;

public interface BasicInfoMapper {
    int insert(BasicInfo record);

    BasicInfo selectByPrimaryKey(Integer id);

    Integer  getByParam(BasicInfo basicInfo);

    int updateByPrimaryKey(BasicInfo basicInfo);

    List<BasicInfo> getAllById(List<Integer> ids);

    void deleteByList(List<Integer> ids);

    Integer addBatch(List<BasicInfo> basicInfoList);

    List<BasicInfo> getByNames(List<String> names);
}