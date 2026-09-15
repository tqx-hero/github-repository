package com.example.test.strings;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/2/25 12:50
 */
public class EqualsTest {

    public static void main(String[] args) {
        List<Integer> list = Stream.of(1,2,3,4).collect(Collectors.toList());
        List<Integer> list2 = new ArrayList<>();
        list2.addAll(list);
        System.out.println(Objects.deepEquals(list, list2));
        new ArrayList<>();
    }
}
