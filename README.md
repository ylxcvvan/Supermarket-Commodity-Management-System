# Supermarket-Commodity-Management-System超市商品管理系统
## 介绍
成都大学22级软件工程课程实践项目大作业，该项目是基于Qt5开发的超市商品管理系统。这是一个用于管理超市商品的系统，具有库存管理、商品分类和销售记录等功能。

## 使用的开源库
本项目使用了以下开源库：

- **图形化界面库**: 本项目的图形化界面库来自于[qt-material-widgets ](https://github.com/laserpants/qt-material-widgets)，该库遵循BSD-3开源协议。



## 实验报告
![Uploading 图片.png…](https://github.com/ylxcvvan/Supermarket-Commodity-Management-System/blob/main/ReadmeImages/image-20240523152920649.png)


### 课程信息

- **课程名称**: 软件工程
- **任课教师**: 覃 艳
- **学院**: 计算机学院
- **专业**: 软件工程
- **年级**: 2022级
- **班级**: 1班
- **开课时间**: 2023 至 2024 学年第 2 学期

### 学生信息

- **组长**:
  - **姓名**: **骆智敏**
  - **学号**: 202210414124

- **组员**:
  - **完颜成煜**:
    - **学号**: 202210414109
  - **陈柱明**:
    - **学号**: 202210414119
  - **王荣**:
    - **学号**: 202210414101
  - **董建博**:
    - **学号**: 202210414129
  - **杨凯光**:
    - **学号**: 202210414113
  - **刘英豪**:
    - **学号**: 202210414123



### 软件运行图:

![image-20240523153300641](https://github.com/ylxcvvan/Supermarket-Commodity-Management-System/blob/main/ReadmeImages/image-20240523153234798.png)

![image-20240523153323957](https://github.com/ylxcvvan/Supermarket-Commodity-Management-System/blob/main/ReadmeImages/image-20240523153300641.png)

![image-20240523153234798](https://github.com/ylxcvvan/Supermarket-Commodity-Management-System/blob/main/ReadmeImages/image-20240523153323957.png)

![image-20240523153337738](https://github.com/ylxcvvan/Supermarket-Commodity-Management-System/blob/main/ReadmeImages/image-20240523153337738.png)

## 数据库：MYSQL

### 建表

先建个数据库，scmsdb,然后用下面语句建表

```mysql
use scmsdb;

CREATE TABLE vip_table (
    Id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(255),
    PhoneNumber VARCHAR(255) NOT NULL,
    Point DOUBLE,
    Level INT,
    RegisterDate DATE
)AUTO_INCREMENT=10001;

CREATE TABLE admin_table (
    Account VARCHAR(255) NOT NULL PRIMARY KEY,
    Password VARCHAR(255) NOT NULL,
    LastLoginDate DATETIME
);

CREATE TABLE cashier_table (
		Id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
		Name VARCHAR(255),
    Account VARCHAR(255) NOT NULL,
    Password VARCHAR(255) NOT NULL,
    LastLoginDate DATETIME
)AUTO_INCREMENT=10001;

CREATE TABLE commodityItem_table(
	Id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
	Name VARCHAR(255) NOT NULL,
	Details TEXT,
	Category VARCHAR(10)
);

CREATE TABLE commodity_table (
		Id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
		ItemId INT NOT NULL,
    Price DOUBLE,
    CostPrice DOUBLE,
    SellByTime DATE,
		FOREIGN KEY (ItemId) REFERENCES commodityItem_table(Id)
)AUTO_INCREMENT=1001;

CREATE TABLE order_table (
    OrderId INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    OrderDate DATETIME NOT NULL,
    OrderState INT NOT NULL,
    TotalPrice DOUBLE,
		PaidPrice DOUBLE,
    ConsumerId INT,
		CashierId INT,
		FOREIGN KEY(CashierId) REFERENCES cashier_table(Id)
)AUTO_INCREMENT=100001;

CREATE TABLE orderItem_table (
    Id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
		OrderId INT,
    CommodityId INT NOT NULL,
    CommodityAmount DOUBLE NOT NULL,
    TotalPrice DOUBLE,
    FOREIGN KEY (CommodityId) REFERENCES commodity_table(Id),
    FOREIGN KEY (OrderId) REFERENCES order_table(OrderId)
);


CREATE TABLE inventory_table (
		Id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
	  CommodityId INT NOT NULL,
    CommodityAmount DOUBLE NOT NULL,
		FOREIGN KEY (CommodityId) REFERENCES commodity_table(Id)
);

```



### 插入初始数据

```mysql
use scmsdb;

-- 插入收银员信息和管理员信息

INSERT INTO admin_table(Account,Password,LastLoginDate)
VALUES ('admin','123456','2024-05-01 08:30:00');

INSERT INTO cashier_table(Name,Account,Password,LastLoginDate)
VALUES ('狄仁杰','wozuimei15','123456','2024-04-10 08:30:00'),
	   ('动力小子','powerkid666','12345678','2024-04-10 08:30:00');

-- 插入vip表
INSERT INTO vip_table (Id,Name, PhoneNumber, Point, Level, RegisterDate) 
VALUES (10000,'无', '无', 0.0, 0, '2024-01-01');

INSERT INTO vip_table (Name, PhoneNumber, Point, Level, RegisterDate) 
VALUES ('张三', '13812345678', 0.0, 1, '2024-01-01'),
       ('李四', '13987654321', 100.0, 2, '2023-05-10'),
       ('王五', '13611112222', 50.0, 2, '2024-03-15');
			 
-- 插入商品项目表 
INSERT INTO commodityItem_table (Name, Details,Category) VALUES 
('可乐', '可乐是一种碳酸饮料，具有独特的甜味和气泡口感。','食品类'),
('雪碧', '雪碧是一种清凉的碳酸饮料，具有清爽的柠檬味。','食品类'),
('洗洁精', '洗洁精是一种清洁剂，常用于洗涤碗碟和餐具，具有强力去污能力。','日用品类'),
('毛巾', '毛巾是一种用于擦拭身体或物品的布料制品，常用于洗浴和清洁。','日用品类'),
('洗脸盆', '洗脸盆是一种用于洗脸的容器，常用于卫生间或洗漱台上。','日用品类');

-- 插入实际的商品表

INSERT INTO commodity_table (ItemId, Price, CostPrice, SellByTime) VALUES 
(1, 2.5, 1.5, '2025-05-10'),
(1, 2.5, 1.5, '2025-06-30'),
(2, 3.0, 2.0, '2025-06-12'),
(2, 3.0, 2.2, '2025-07-31'),
(3, 5.0, 3.0, '2025-06-30'),
(3, 5.5, 3.0, '2025-06-20'),
(4, 10.0, 7.4, '2025-05-15'),
(4, 10.0, 8.0, '2025-06-26'),
(5, 8.5, 6.2, '2025-06-30'),
(5, 8.5, 6.0, '2025-06-01');

-- 先插入订单

INSERT INTO order_table (OrderDate, OrderState, TotalPrice,PaidPrice, ConsumerId,CashierId) 
VALUES ('2024-05-13 08:30:00', 1, 20.00,18.00, 10000,10001),
       ('2024-05-14 09:45:00', 1, 80.00,80.00, 10000,10001),
       ('2024-05-15 10:30:00', 1, 120.00,100.00, 10001,10001),
       ('2024-05-17 12:00:00', 1, 90.00, 90,10002,10001);

-- 在插入订单表项

-- 插入订单1的订单项
INSERT INTO orderItem_table (OrderId, CommodityId, CommodityAmount, TotalPrice) 
VALUES (100001, 1001, 8.0, 20.0);

-- 插入订单2的订单项
INSERT INTO orderItem_table (OrderId, CommodityId, CommodityAmount, TotalPrice) 
VALUES (100002, 1003, 10.0, 30.0),
       (100002, 1005, 10.0, 50.0);

-- 插入订单3的订单项
INSERT INTO orderItem_table (OrderId, CommodityId, CommodityAmount, TotalPrice) 
VALUES (100003, 1003, 20.0, 60.0),
       (100003, 1004, 20.0, 60.0);

-- 插入订单4的订单项
INSERT INTO orderItem_table (OrderId, CommodityId, CommodityAmount, TotalPrice) 
VALUES (100004, 1002, 2.0, 5.0),
       (100004, 1010, 10, 85.0);
			 


-- 库存信息插入

INSERT INTO inventory_table (CommodityId, CommodityAmount) 
VALUES (1001, 100.0),
       (1002, 200.0),
       (1003, 150.0),
       (1004, 250.0),
       (1005, 120.0);
			 
INSERT INTO inventory_table (CommodityId, CommodityAmount) 
VALUES (1006, 39.0),
       (1007, 212.0),
       (1008, 132.0),
       (1009, 56.0),
       (1010, 23.0);


```

### 为Qt配置Mysql数据库驱动

https://zhuanlan.zhihu.com/p/676716832

打开这个，按教程弄好数据库

### 表关系：

**满足3范式标准**

![image-20240523202906340](https://github.com/ylxcvvan/Supermarket-Commodity-Management-System/blob/main/ReadmeImages/image-20240523202906340.png)
