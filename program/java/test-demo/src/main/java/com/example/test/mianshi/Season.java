package com.example.test.mianshi;

public enum Season {

    SPRING("春天", "生机怏然"),
    SUMMER("夏天", "勃勃生机"),
    AUTUMN("秋天", "硕果累累"),
    WINTER("冬天", "银装素裹");
    private final String seasonName;

    private final String seasonDesc;

    private Season(String seasonDesc, String seasonName) {
        this.seasonDesc = seasonDesc;
        this.seasonName = seasonName;
    }
}
