# CSS selector

[rules details](https://blog.csdn.net/qq_33472765/article/details/80740097)

## 1 基本css选择器

| 选择器         | 描述                                                         | 举例      |
| -------------- | ------------------------------------------------------------ | --------- |
| *              | 通配选择器，选择所有的元素                                   | *         |
| <type>         | 选择特定类型的元素，支持基本HTML标签                         | h1        |
| .<class>       | 选择具有特定class的元素                                      | .class1   |
| <type>.<class> | 特定类型和特定class的交集（直接将多个选择器连着一起表示交集） | h1.class1 |
| \#<id>         | 选择具有特定id属性值的元素                                   | #id1      |

## 2 属性选择器

| 选择器 |  描述    | 举例 |
| ------ | ---- | -------- |
| [attr] | 选取定义attr属性的元素，即使该属性没有值 | [placeholder] |
| [attr="val"] | 选取attr属性等于val的元素 | [placeholder="请输入关键词"] |
| [attr^="val"] | 选取attr属性开头为val的元素 | [placeholder^="请输入"] |
| [attr$="val"] | 选取attr属性结尾为val的元素 | [placeholder$="关键词"] |
| [attr*="val"] | 选取attr属性包含val的元素 | [placeholder*="入关"] |
| [attr~="val"] | 选取attr属性包含多个空格分隔的属性，其中一个等于val的元素 | [placeholder~="关键词"] |
| [attr\|="val"] | 选取attr属性等于val的元素或第一个属性值等于val的元素 | [placeholder\|="关键词"] |


