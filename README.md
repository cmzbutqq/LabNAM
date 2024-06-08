# LabNAM

## A. 环境配置

**参考这个教程的第二P：** https://www.bilibili.com/video/BV1Za4y1v7ra/?p=2

*注意事项*：

1. opencv不能下最新版（除非你Qt Creator有msvc2022），我用的是opencv4.5.1.

2. Qt Creator的**MSVC如果不能使用**，参照 https://www.cnblogs.com/astonc/p/16799950.html 进行配置。

3. 如果**qt项目无法运行**，试试以下几个方法：
   
   - 排除路径中的中文与空格
   
   - 重启qt creator
   
   - 重启电脑
   
   - 将qt的构建模式从release切到debug
   
   - 多点几次运行图标
   
   - 自求多福

4. 我用的版本：**Qt Creator 4.11.1，MSVC 2017 64bit，Qt 5.14.1，opencv-4.5.1-vc14_vc15**.

5. **为了与本项目的库路径相匹配**（不然需要改目录），将你下载的 opencv-4.5.1-vc14_vc15.exe 用解压工具 (如7zip) 解压，并将opencv-4.5.1-vc14_vc15.exe\opencv\ 里面的多个文件与文件夹（像是build, sources, LICENSE.txt, LICENSE_FFMPEG.txt, README.md.txt 这些）放到 C:\opencv-4.5.1 目录下，全局变量的设置等请参考前面给出的b站视频（文件路径会与视频中的有少许不同）
