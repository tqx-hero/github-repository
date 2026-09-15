package com.spring.db;

import com.spring.db.service.UserService;
import jakarta.annotation.Resource;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.EnableAspectJAutoProxy;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.transaction.annotation.EnableTransactionManagement;
import org.springframework.transaction.annotation.Transactional;

import javax.sql.DataSource;
import java.sql.SQLException;

@SpringBootTest
class DbApplicationTests {

    @Resource
    private DataSource source;

    @Resource
    private UserService userService;

    @Test
    void contextLoads() throws SQLException {
    }

    @Test
    void testUpdate() throws InterruptedException {
//        int update = userService.update(4, "five12");
//        System.out.println(userService.getClass());
//        userService.select(1);
        userService.mixedService();
//        userService.delete(1);
    }

    @Test
    void testInsert() {
//        String sql = "INSERT INTO basic_info (id, name) VALUES (?, ?)";
//        int num = jdbcTemplate.update(sql, 4, "张晕");
//        int a = 1 / 0;
//        assert num == 4 : "操作成功";

    }


}
