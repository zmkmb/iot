# 使用nodemcu制作开机棒
+ 搭建开发环境

  + 下载Arduino编辑器
  + 开发板管理器新增esp8266

  文件->首选项->附加开发板管理网址，添加

  https://arduino.esp8266.com/stable/package_esp8266com_index.json

  工具->开发板->开发板管理器,搜索esp8266安装

  + 安装库

  项目->加载库->管理库

  安装AliyunloTSDK,ArduinoJson,Crypto,PubSubClient库

+ 申请阿里云账号

  - 创建产品
  - 功能定义
  - 添加设备

+ 修改代码

```
//修改为自己的key和密钥
#define PRODUCT_KEY "xxx"
#define DEVICE_NAME "xxx"
#define DEVICE_SECRET "xxxx"
//修改wifi账号密码
#define WIFI_SSID "wifi"//网络名
#define WIFI_PASSWD "123456"//wifi密码
```
+ 烧录

  Arduino编辑器中点击上传按钮

- 测试

 阿里云管理后台，物联网平台->选择设备->查看->在线调试->调试功能（选择mac地址）->方法(选择设置)

```
{
  "MACAddress": "00:11:cc:ff:44:66"//填写自己电脑的mac地址
}
```

点击发送指令