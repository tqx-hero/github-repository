package com.example.demo.mapper;

import com.example.demo.entity.Location;
import com.example.demo.entity.StatusCode;
import org.apache.ibatis.annotations.Param;

import java.util.List;

public interface LocationMapper {
    int deleteByPrimaryKey(Integer id);

    int insert(Location record);

    int insertSelective(Location record);

    Location selectByPrimaryKey(Integer id);

    int updateByPrimaryKeySelective(Location record);

    int updateByPrimaryKey(Location record);

    /**
     * 条件查询所有
     * @param nameId
     */
    List<Location> selectAll(@Param("nameId") Integer nameId);
    /**
     * 根据NameIds查询
     * @param nameIds
     */
    List<Location> getAllByList(List<Integer> nameIds);
    /**
     * 根据ids查询
     * @param ids
     */
    List<Location> getAllByIds(List<Integer> ids);
}