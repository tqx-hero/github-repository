//
// Created by Administrator on 2026/7/18.
//
#include <fstream>
#include <iostream>
//ASCII文件的读取
void cpyFile() {
    std::string filePath = "E:\\program\\c++\\learning\\learn\\file\\";
    std::ifstream is(filePath + "source.txt", std::ios::in);
    std::ofstream os(filePath + "target.txt", std::ios::out);
    // std::ofstream os(filePath + "target.txt", std::ios::out | std::ios::app);
    if (!is || !os) {
        if (is)
            is.close();
        if (os)
            os.close();
        throw std::runtime_error("打开文件失败");
    }
    const int len = 1024;
    unsigned int count = 0;
    char buffer[len] = {0};
    //通过read函数读取文件
    while (is.read(buffer, len)) {
        os.write(buffer, len);
    }
    if (count = is.gcount())
        os.write(buffer, count);
    //以单个字符读取的形式读取字符
    // while (is.get(ch)) {
    //     buffer[len++] = ch;
    //     if (len >= 1024) {
    //         os.write(buffer, len);
    //         len = 0;
    //     }
    // }
    // if (len)
    //     os.write(buffer, len);

    is.close();
    os.close();
}

class Persion {
public:
    Persion(int age, int num)
        : age(age),
          num(num) {
    }

    Persion() : age(0), num(0) {
    };

    [[nodiscard]] int getAge() const {
        return age;
    }

    void setAge(int age) {
        this->age = age;
    }

    [[nodiscard]] int getNum() const {
        return num;
    }

    void setNum(int num) {
        this->num = num;
    }

private:
    int age;
    int num;
};

//以二进制的形式将数据拷贝到文件中
void cpyFileByBinary() {
    using namespace std;
    std::string filePath = "E:\\program\\c++\\learning\\learn\\file\\";
    std::ofstream os(filePath + "target.txt", ios::binary | ios::out);
    if (!os)
        throw runtime_error("文件不存在");
    Persion p1(10, 20), p2(30, 40);
    os.write(reinterpret_cast<char *>(&p1), sizeof(Persion));
    os.write(reinterpret_cast<char *>(&p2), sizeof(Persion));
    os.close();
}

//读取二进制文件
//原理是将二进制文件按照字节(char)逐一读取出来
//定义对象，指向对象的指针，必须为char*类型（因为要按照字节方式往内存中复制）
//后面就是把读取出来的字节依次放入指针指向的区域，并将指针后移，直到全部填充完毕
void readBinaryFile() {
    using namespace std;
    std::string filePath = "E:\\program\\c++\\learning\\learn\\file\\";
    ifstream is(filePath + "target.txt", ios::binary | ios::in);
    if (!is)
        throw runtime_error("文件不存在");
    Persion p1, p2;
    //按照字节方式一个字节一个字节进去
    // char *ptr = reinterpret_cast<char *>(&p1);
    // char ch;
    // while (is.get(ch)) {
    //     *ptr = ch;
    //     ptr++;
    // }

    //将对象所在空间解读成char类型指针，通过read函数直接读取若干字节
    is.read(reinterpret_cast<char *>(&p1), sizeof(Persion));
    is.read(reinterpret_cast<char *>(&p2), sizeof(Persion));

    cout << p1.getAge() << " " << p1.getNum() << endl;
    cout << p2.getAge() << " " << p2.getNum() << endl;
    is.close();
}
#if 0
int main() {
    try {
        // cpyFile();
        // cpyFileByBinary();
        readBinaryFile();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
#endif
