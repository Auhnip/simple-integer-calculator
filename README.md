# 简单整数计算器

## 功能说明

- 每行可输入一个算数表达式并得出结果；
- 输入 `quit` 或算术表达式不符合语法要求时，退出程序；
- 支持的运算符包含： `+, -, *, /, ^, (, )` ；
- 只能够对整数进行运算；
- 幂运算中，指数仅能为自然数，即非负整数；
- 对于算术表达式中大于 `5` 位的整数，认定为语法错误；
- 对于运算的中间结果或最终结果，范围若超过 `[-2^63, 2^63)` ，所得计算结果不保证正确性；
- 不允许多余的 `+` 来标识正数，如 `1 + +3` 或 `12 + (+64)` ；
- 数字与运算符之间可以包含任意数量的空白符；

## 输入样例

### 合法的表达式

```text
-1+2-4/2+(6/3)^4
3*4^3 /   3
7+10- 2  ^ 10 / 2
-32
```

### 非法的表达式

```text
123456 + 1
2 ^ 64 - 2 ^ 64
3 --
+64
5 % 2
2^ (-1)
```
