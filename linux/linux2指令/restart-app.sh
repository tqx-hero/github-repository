#!/bin/bash
# 定义镜像名和容器名
IMAGE_NAME="demo-app"
CONTAINER_NAME="demo-app"

# 停止并删除旧容器
echo "停止容器 $CONTAINER_NAME..."
docker stop $CONTAINER_NAME > /dev/null 2>&1
docker rm $CONTAINER_NAME > /dev/null 2>&1

# 重构镜像
echo "重新构建镜像 $IMAGE_NAME..."
docker build --no-cache -t $IMAGE_NAME .

# 启动新容器（根据你的实际需求修改run参数）
echo "启动新容器..."
docker run -d --name $CONTAINER_NAME -p 9000:9000 $IMAGE_NAME

echo "容器重启完成！"