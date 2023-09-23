## 使用须知

- PHP7.x 请使用v1.0.0分支或者1.0.0发行版
  ```
  git clone -b v1.0.0 https://gitee.com/lfveeker/tonyenc.git
  ```
- master分支已移除对PHP7.x的支持。

## 介绍

- 一个简洁、高性能、跨平台的 PHP7 PHP8 代码加密扩展，当前版本为 1.0.1
- 因```lihancong/tonyenc```已不再维护，特开此项目对PHP7.4+进行支持

## 特点

- 简单快速，经实测，几乎不影响性能
- 兼容 OPCache、Xdebug等其他扩展
- 兼容 Linux、macOS、Windows等系统
- 兼容 Apache、Nginx + PHP-FPM、CLI等运行模式
- 加密算法较简单，这是出于速度考虑，但仍不易解密
- 若项目的php文件很多，建议只加密部分重要代码文件
- 要求 PHP >= 7.0

**加密前记得备份!!!**

## 安装

编译前请在 core.h 中做如下修改:

```c
/* 这里定制你的加密特征头，不限长度，十六进制哦 */
const u_char tonyenc_header[] = {
        0x66, 0x88, 0xff, 0x4f,
        0x68, 0x86, 0x00, 0x56,
        0x11, 0x16, 0x16, 0x18,
};

/* 这里指定密钥，长一些更安全 */
const u_char tonyenc_key[] = {
        0x9f, 0x49, 0x52, 0x00,
        0x58, 0x9f, 0xff, 0x21,
        0x3e, 0xfe, 0xea, 0xfa,
        0xa6, 0x33, 0xf3, 0xc6,
};
```

#### 在 Linux、macOS 上编译

```
PHP7请拉取v1.0.0分支:
git clone -b v1.0.0 https://gitee.com/lfveeker/tonyenc.git
PHP8:
git clone https://gitee.com/lfveeker/tonyenc.git
cd tonyenc
phpize
./configure --with-php-config=php-config path
make
make install
```

将编译好的文件 tonyenc.so 加入到配置项 extension=tonyenc.so，重启 PHP 服务

#### 在 Windows上安装

```
已编译了以下模块，可供测试（这里的密钥与源代码中的相同）:
7.0~7.1版本需要安装有 VC14 运行库
7.2~7.4版本需要安装有 VC15 运行库
8.0+版本需要安装有 VS16 运行库 
NTS:Non Thread Safe(非线程安全)
TS:Thread Safe(线程安全)
x64:64位
x86:32位
eg:
# php7.4 64位 非线程安全版
php_tonyenc-1.0.0-7.4-nts-vc15-x64.dll
# php7.4 32位 非线程安全版
php_tonyenc-1.0.0-7.4-nts-vc15-x86.dll
# php7.4 64位 线程安全版
php_tonyenc-1.0.0-7.4-ts-vc15-x64.dll
# php7.4 32位 线程安全版
php_tonyenc-1.0.0-7.4-ts-vc15-x86.dll
其他版本不再赘述，可用的dll文件均在windows-dll目录，请根据自己的PHP版本选择对应的dll
```

- 自定义密钥后构建Windows版扩展请参照build_windows_dll.pdf所提供的步骤。

## 加密

代码中的 `tonyenc.php` 是加密工具:

```bash
php tonyenc.php example.php dir/
```

这样即可加密 `example.php` 和 `dir` 目录下的所有 php 文件，PHP 在运行它们时会自动解密，够简单吧！

