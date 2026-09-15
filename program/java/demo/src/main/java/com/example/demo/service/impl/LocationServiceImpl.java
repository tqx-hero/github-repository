package com.example.demo.service.impl;

import com.example.demo.entity.BasicInfo;
import com.example.demo.entity.Location;
import com.example.demo.entity.Result;
import com.example.demo.mapper.BasicInfoMapper;
import com.example.demo.mapper.LocationMapper;
import com.example.demo.service.LocationService;
import com.example.demo.util.ResultUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/2/17 8:27
 */
@Service
public class LocationServiceImpl implements LocationService {

    @Autowired
    private LocationMapper locationMapper;
    @Autowired
    private BasicInfoMapper basicInfoMapper;

    @Override
    public List<Location> findAll(Integer nameId) {
        if (Objects.equals(String.valueOf(nameId), "")) {
            nameId = null;
        }
        return locationMapper.selectAll(nameId);
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public Result<String> add(Location location) {

        Location key = locationMapper.selectByPrimaryKey(location.getId());
        if (Objects.nonNull(key)) {
            return ResultUtils.failure("ID重复，请重新输入！");
        }

        BasicInfo basicInfo = basicInfoMapper.selectByPrimaryKey(location.getNameId());

        if (Objects.isNull(basicInfo)) {
            return ResultUtils.failure("nameId没有相关人员，请重新输入!");
        }

        return locationMapper.insert(location) == 1
                ? ResultUtils.success() : ResultUtils.failure();
    }

    @Override
    public Result<List<Location>> getAllByIds(List<BasicInfo> basicInfoList) {
        if (Objects.nonNull(basicInfoList)) {
            List<Integer> ids= basicInfoList.stream().map(BasicInfo::getId).collect(Collectors.toList());
            return  ResultUtils.success(locationMapper.getAllByList(ids));
        }
        return null;
    }

    @Override
    public List<Location> findAll(List<Integer> ids) {
        return locationMapper.getAllByIds(ids);
    }
}
