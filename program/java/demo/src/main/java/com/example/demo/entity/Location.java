package com.example.demo.entity;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.validation.constraints.NotNull;
import java.io.Serializable;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class Location implements Serializable {
    private static final long serialVersionUID = 25815813817418359L;
    @NotNull(message = "id不能为空！")
    private Integer id;

    private String location;

    @NotNull(message = "人物ID不能为空！")
    private Integer nameId;

}