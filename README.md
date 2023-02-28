# Decoder

## 分支对应关系
```
master：ARM
x86: x86
mips: mips
power: power
riscv: riscv
sparc: sparc
```

## 运行环境
与gem5的运行环境相同

## 编译
```
mkdir -p build
cd build
cmake ..
make -j 16
```

## 运行
在编译后会生成可执行文件main，可接收一个指令参数，运行后会输出指令的opcode信息
```
./main 885f7c40
```

## 入口文件 main.cc
```
包含了decoder使用和debug代码
```

## 关键函数以及路径
```
以arm为例
arch/arm/decoder.hh
    decode_inst: 解析指令
    precode/postdecode: 分阶段处理
    decode_opcode: 仅解析opcode
    decode_mem: 仅解析mem信息
```