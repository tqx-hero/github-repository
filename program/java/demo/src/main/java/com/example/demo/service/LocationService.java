package com.example.demo.service;

import com.example.demo.entity.BasicInfo;
import com.example.demo.entity.Location;
import com.example.demo.entity.Result;

import java.util.List;

public interface LocationService {
    List<Location> findAll(Integer nameId);

    Result<String> add(Location location);

    Result<List<Location>> getAllByIds(List<BasicInfo> basicInfoList);

    List<Location> findAll(List<Integer> ids);
}
