package com.example.demo.entity;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import java.io.Serializable;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class BasicInfo implements Serializable {

    private static final long serialVersionUID = 2537161544189698383L;
    @NotNull(message = "ID不能为空！")
    private Integer id;

    @NotBlank(message = "姓名不能为空！")
    private String name;

}