package com.example.demo.controller;

import com.example.demo.entity.BasicInfo;
import com.example.demo.entity.Location;
import com.example.demo.entity.Result;
import com.example.demo.service.LocationService;
import com.example.demo.util.ResultUtils;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiImplicitParams;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/2/17 8:24
 */
@Api(tags = "地址管理")
@RestController
@RequestMapping("/location")
public class LocationController {

    @Autowired
    private LocationService locationService;


    @ApiOperation(value = "根据nameId查询地址", notes = "地址查询")
    @ApiImplicitParams({
//            @ApiImplicitParam(name = "phoneNumber", value = "电话号码", required = true, dataType = "string"),
//            @ApiImplicitParam(name = "status", value = "状态", required = true),
            @ApiImplicitParam(name = "nameId", value = "nameId", required = false, dataType = "int")
    })
    @GetMapping("/list")
    public Result<List<Location>> findAll(Integer nameId) {
        return ResultUtils.success(locationService.findAll(nameId));
    }

    @ApiOperation(value = "添加位置信息", notes = "添加位置信息")
//    @ApiImplicitParams({
//            @ApiImplicitParam(name = "id", value = "Id", required = true, dataType = "int"),
//            @ApiImplicitParam(name = "location", value = "地址", required = false , dataType = "string"),
//            @ApiImplicitParam(name = "nameId", value = "nameId", required = true, dataType = "int")
//    })
    @PostMapping("/add")
    public Result<String> insert(@RequestBody @Valid Location location) {
        return locationService.add(location);
    }

    @ApiOperation(value = "根据nameId查询地址", notes = "地址查询")
    @PostMapping("/list_all")
    public Result<List<Location>> getAll(@RequestBody List<BasicInfo> basicInfoList) {
        return locationService.getAllByIds(basicInfoList);
    }

    @ApiOperation(value = "根据Id查询地址", notes = "根据Id查询地址")
//    @ApiImplicitParams({
////            @ApiImplicitParam(name = "phoneNumber", value = "电话号码", required = true, dataType = "string"),
////            @ApiImplicitParam(name = "status", value = "状态", required = true),
//            @ApiImplicitParam(name = "nameId", value = "nameId", required = false, dataType = "int")
//    })
    @PostMapping("/list_by_ids")
    public Result<List<Location>> findAll(@RequestBody(required = false) List<Integer> ids) {
        return ResultUtils.success(locationService.findAll(ids));
    }

}
