package com.example.demo.service.impl;

import com.example.demo.entity.BasicInfoVO;
import com.example.demo.entity.Location;
import com.example.demo.mapper.BasicInfoMapper;
import com.example.demo.entity.BasicInfo;
import com.example.demo.entity.Result;
import com.example.demo.mapper.LocationMapper;
import com.example.demo.service.BasicInfoService;
import com.example.demo.util.ResultUtils;
import com.google.common.base.Supplier;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.sound.sampled.Port;
import java.util.*;
import java.util.stream.Collectors;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/2/15 23:10
 */
@Service
public class BasicInfoServiceImpl implements BasicInfoService {


    @Autowired
    private BasicInfoMapper basicInfoMapper;
    @Autowired
    private LocationMapper locationMapper;

    @Override
    @Transactional(rollbackFor = Exception.class)
    public Result<String> add(BasicInfo basicInfo) {
        Integer num = basicInfoMapper.getByParam(new BasicInfo(basicInfo.getId(), null));
        if (num > 0) {
            return ResultUtils.failure("个人Id已存在，请重新输入！");
        }
        Integer numByName = basicInfoMapper.getByParam(new BasicInfo(null, basicInfo.getName()));
        if (numByName > 0) {
            return ResultUtils.failure("个人名称已存在，请重新输入！");
        }
        int i = basicInfoMapper.insert(basicInfo);
        return i == 1 ? ResultUtils.success() : ResultUtils.failure();
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public Result<String> update(BasicInfo basicInfo) {
        Integer num = basicInfoMapper.getByParam(new BasicInfo(basicInfo.getId(), null));
        if (num == 0) {
            return ResultUtils.failure("个人ID不存在，请重新输入！");
        }
        return basicInfoMapper.updateByPrimaryKey(basicInfo) == 1 ? ResultUtils.success() : ResultUtils.failure();
    }

    @Override
    public Result<List<BasicInfoVO>> listAll(List<Integer> ids) {
        if (ids == null || ids.size() == 0) {
            return ResultUtils.failure("请输入要查询的人员ID");
        }
        List<BasicInfoVO> basicInfoVOList = new ArrayList<>();
        List<BasicInfo> basicInfoList = basicInfoMapper.getAllById(ids);
        if (Objects.nonNull(basicInfoList) && !basicInfoList.isEmpty()) {
            List<Location> locationList = locationMapper.getAllByList(basicInfoList.stream().
                    map(BasicInfo::getId).collect(Collectors.toList()));

            basicInfoList.forEach(bl -> {
                Set<Location> locations = new HashSet<>();
                BasicInfoVO basicInfoVO = new BasicInfoVO(bl, null);

                if (Objects.nonNull(locationList) && !locationList.isEmpty()) {
                    locationList.forEach(location -> {
                        Boolean b = location.getNameId().equals(bl.getId()) ?
                                locations.add(location) : null;
                    });
                }
                basicInfoVO.setLocations(locations);
                basicInfoVOList.add(basicInfoVO);
            });
        }
        return ResultUtils.success(basicInfoVOList);
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public Result<String> delete(List<Integer> ids) throws Exception {
        if (ids == null || ids.isEmpty()) {
            return ResultUtils.failure("请输入ID");
        }

        basicInfoMapper.deleteByList(ids);

        return ResultUtils.success();
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public Result<String> addBatch(List<BasicInfo> basicInfoList) {
        if (Objects.isNull(basicInfoList)) {
            return ResultUtils.failure("请输入用户信息！");
        }
        List<Integer> integerList = basicInfoList.stream().map(BasicInfo::getId).collect(Collectors.toList());
        List<BasicInfo> infoList = basicInfoMapper.getAllById(integerList);
        if (Objects.nonNull(infoList) && !infoList.isEmpty()) {
            return ResultUtils.failure("写入的ID列表已存在！");
        }
        List<String> stringList = basicInfoList.stream().map(BasicInfo::getName).collect(Collectors.toList());
        List<BasicInfo> infoLists =  basicInfoMapper.getByNames(stringList);
        if (Objects.nonNull(infoLists) && !infoLists.isEmpty()) {
            return ResultUtils.failure("写入的name列表已存在！");
        }
        return basicInfoMapper.addBatch(basicInfoList) == basicInfoList.size()
                ? ResultUtils.success("添加成功") : ResultUtils.failure("添加失败");
    }
}
