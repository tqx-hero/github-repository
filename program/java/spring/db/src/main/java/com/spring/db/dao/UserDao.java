package com.spring.db.dao;

import com.spring.db.entity.UserVO;
import jakarta.annotation.Resource;
import org.springframework.boot.autoconfigure.security.SecurityProperties;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.PreparedStatementSetter;
import org.springframework.stereotype.Repository;
import org.springframework.transaction.annotation.Transactional;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/11 15:39
 */
@Repository
public class UserDao {

    private final JdbcTemplate jdbcTemplate;

    public UserDao(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    public int insert(Integer id, String name) {
        int update = jdbcTemplate.update("insert into basic_info (id, name) values (?, ?)", id, name);
        return update;
    }

    public int update(Integer id, String name) {
        int i = jdbcTemplate.update("update basic_info set name = ? where id = ?", name, id);
        return i;
    }

    public int delete(Integer id) {
        int i = jdbcTemplate.update("delete from basic_info where id = ?", id);
        return i;
    }

    public Object select(Integer id) {
        String sql = "select * from basic_info where id = ?";
        UserVO vo = jdbcTemplate.queryForObject(sql, UserVO.class, id);
        return vo;
    }

}
