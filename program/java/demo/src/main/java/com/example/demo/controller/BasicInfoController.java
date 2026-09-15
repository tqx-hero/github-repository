package com.example.demo.controller;

import com.example.demo.entity.BasicInfo;
import com.example.demo.entity.BasicInfoVO;
import com.example.demo.entity.Result;
import com.example.demo.entity.UserDemo;
import com.example.demo.service.BasicInfoService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.RequiredArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;
import java.util.ArrayList;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/2/15 22:14
 */
@Api(tags = "人员基本信息管理")
@RestController
@RequestMapping("/info")
@RequiredArgsConstructor
public class BasicInfoController {

    private final BasicInfoService basicInfoService;

    @ApiOperation(value = "添加基本人员", notes = "添加基本人员")
    @PostMapping("/add")
    public Result<String> add(@RequestBody @Valid BasicInfo basicInfo) {
        return basicInfoService.add(basicInfo);
    }

    @ApiOperation(value = "修改基本人员", notes = "修改基本人员")
    @PostMapping("/update/{id}")
    public Result<String> update(@PathVariable("id") Integer id, @RequestBody BasicInfo basicInfo) {
        basicInfo.setId(id);
        return basicInfoService.update(basicInfo);
    }

    @ApiOperation(value = "根据ID查询人员所有信息", notes = "根据ID查询人员所有信息")
    @PostMapping("/get_all")
    public Result<List<BasicInfoVO>> listAll(@RequestBody(required = false) List<Integer> ids) {
        return basicInfoService.listAll(ids);
    }

    @ApiOperation(value = "批量删除", notes = "批量删除")
    @DeleteMapping("/delete")
    public Result<String> delete(@RequestBody List<Integer> ids) throws Exception {
        return basicInfoService.delete(ids);
    }

    @ApiOperation(value = "批量增加", notes = "批量增加")
    @PostMapping("/add_batch")
    public Result<String> addBatch(@RequestBody List<BasicInfo> basicInfoList) {
        return basicInfoService.addBatch(basicInfoList);
    }

    /**
     * 模拟死循环CPU利用率彪高的问题
     */
    @ApiOperation(value = "cpu飙高模拟", notes = "cpu飙高模拟")
    @GetMapping("/cpu_h")
    public void cpuH() {
        while (true) {

        }
//        return null;
    }

    private static List<UserDemo> list = new ArrayList<>();

    @ApiOperation(value = "内存飙高模拟", notes = "内存飙高模拟")
    @GetMapping("/neicun_h")
    public void neicunH() {
        for (int i = 0; i < 30; i++) {
            list.add(new UserDemo());
        }
    }

}
